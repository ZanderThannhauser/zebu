
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "read_char.h"
#include "read_token.h"

static const enum tokenizer_state {
	
	ts_error,
	
	ts_EOF,
	
	// symbols:
	ts_dot,
	ts_plus,
	ts_vbar,
	ts_comma,
	ts_colon,
	ts_minus,
	ts_qmark,
	ts_emark,
	ts_percent,
	ts_asterisk,
	ts_ampersand,
	ts_semicolon,
	ts_gravemark,
	ts_array_hashtag,
	ts_absolute_path,
	ts_scalar_hashtag,
	ts_string_literal,
	
	// backets:
	ts_oparen, ts_cparen,
	ts_osquare, ts_csquare,
	
	// literals:
	ts_character_literal,
	
	// identifiers:
	ts_identifier,
	
	ts_start,
	
	ts_read_dot,
	ts_read_plus,
	ts_read_vbar,
	ts_read_minus,
	ts_read_comma,
	ts_read_colon,
	ts_read_qmark,
	ts_read_emark,
	ts_read_oparen,
	ts_after_slash,
	ts_read_cparen,
	ts_read_osquare,
	ts_read_csquare,
	ts_read_percent,
	ts_read_asterisk,
	ts_read_semicolon,
	ts_read_gravemark,
	ts_read_ampersand,
	ts_reading_hashtag,
	ts_reading_hashtag2,
	ts_reading_hashtag3,
	ts_skipping_comment,
	ts_reading_hashtag4,
	ts_reading_identifier,
	ts_read_absolute_path,
	ts_read_string_literal,
	ts_reading_absolute_path,
	ts_reading_string_escape,
	ts_reading_string_literal,
	ts_reading_character_escape,
	ts_reading_character_literal1,
	ts_reading_character_literal2,
	ts_reading_character_literal3,
	
	
	number_of_tokenizer_states,
} machine[number_of_tokenizer_states][256] = {
	#define ANY 0 ... 255
	
	// EOF:
	[ts_start]['\0'] = ts_EOF,
	
	// whitespace:
	[ts_start][' '] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// symbols:
	[ts_start]['.'] = ts_read_dot,
		[ts_read_dot][ANY] = ts_dot,
	[ts_start]['+'] = ts_read_plus,
		[ts_read_plus][ANY] = ts_plus,
	[ts_start]['|'] = ts_read_vbar,
		[ts_read_vbar][ANY] = ts_vbar,
	[ts_start][','] = ts_read_comma,
		[ts_read_comma][ANY] = ts_comma,
	[ts_start]['?'] = ts_read_qmark,
		[ts_read_qmark][ANY] = ts_qmark,
	[ts_start]['-'] = ts_read_minus,
		[ts_read_minus][ANY] = ts_minus,
	[ts_start][':'] = ts_read_colon,
		[ts_read_colon][ANY] = ts_colon,
	[ts_start]['!'] = ts_read_emark,
		[ts_read_emark][ANY] = ts_emark,
	[ts_start]['%'] = ts_read_percent,
		[ts_read_percent][ANY] = ts_percent,
	[ts_start]['*'] = ts_read_asterisk,
		[ts_read_asterisk][ANY] = ts_asterisk,
	[ts_start][';'] = ts_read_semicolon,
		[ts_read_semicolon][ANY] = ts_semicolon,
	[ts_start]['`'] = ts_read_gravemark,
		[ts_read_gravemark][ANY] = ts_gravemark,
	[ts_start]['&'] = ts_read_ampersand,
		[ts_read_ampersand][ANY] = ts_ampersand,
	
	// brackets:
	[ts_start]['('] = ts_read_oparen,
		[ts_read_oparen][ANY] = ts_oparen,
	[ts_start][')'] = ts_read_cparen,
		[ts_read_cparen][ANY] = ts_cparen,
	[ts_start]['['] = ts_read_osquare,
		[ts_read_osquare][ANY] = ts_osquare,
	[ts_start][']'] = ts_read_csquare,
		[ts_read_csquare][ANY] = ts_csquare,
	
	// literals:
	[ts_start]['\''] = ts_reading_character_literal1,
		[ts_reading_character_literal1][ANY] = ts_reading_character_literal2,
		[ts_reading_character_literal1]['\\'] = ts_reading_character_escape,
			[ts_reading_character_escape]['\\'] = ts_reading_character_literal2,
			[ts_reading_character_escape]['n'] = ts_reading_character_literal2,
			[ts_reading_character_escape]['t'] = ts_reading_character_literal2,
			[ts_reading_character_escape]['\''] = ts_reading_character_literal2,
			[ts_reading_character_escape]['\"'] = ts_reading_character_literal2,
		[ts_reading_character_literal2]['\''] = ts_reading_character_literal3,
		[ts_reading_character_literal3][ANY] = ts_character_literal,
	
	[ts_start]['\"'] = ts_reading_string_literal,
		[ts_reading_string_literal][ANY] = ts_reading_string_literal,
		[ts_reading_string_literal]['\\'] = ts_reading_string_escape,
			[ts_reading_string_escape][ANY] = ts_reading_string_literal,
		[ts_reading_string_literal]['\"'] = ts_read_string_literal,
			[ts_read_string_literal][ANY] = ts_string_literal,
	
	[ts_start]['#'] = ts_reading_hashtag,
		[ts_reading_hashtag]['a' ... 'z'] = ts_reading_hashtag2,
		[ts_reading_hashtag]['A' ... 'Z'] = ts_reading_hashtag2,
			[ts_reading_hashtag2][ANY] = ts_scalar_hashtag,
			[ts_reading_hashtag2]['_'] = ts_reading_hashtag2,
			[ts_reading_hashtag2]['1' ... '9'] = ts_reading_hashtag2,
			[ts_reading_hashtag2]['a' ... 'z'] = ts_reading_hashtag2,
			[ts_reading_hashtag2]['A' ... 'Z'] = ts_reading_hashtag2,
			[ts_reading_hashtag2]['['] = ts_reading_hashtag3,
				[ts_reading_hashtag3][']'] = ts_reading_hashtag4,
					[ts_reading_hashtag4][ANY] = ts_array_hashtag,

	// identifier:
	[ts_start]['a' ... 'z'] = ts_reading_identifier,
	[ts_start]['A' ... 'Z'] = ts_reading_identifier,
		[ts_reading_identifier][ANY] = ts_identifier,
		[ts_reading_identifier]['_'] = ts_reading_identifier,
		[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
		[ts_reading_identifier]['A' ... 'Z'] = ts_reading_identifier,
	
	// absolute path:
	[ts_start]['<'] = ts_reading_absolute_path,
		[ts_reading_absolute_path][ANY] = ts_reading_absolute_path,
		[ts_reading_absolute_path]['>'] = ts_read_absolute_path,
			[ts_read_absolute_path][ANY] = ts_absolute_path,
	
};

static void append(struct tokenizer* this, char c)
{
	ENTER;
	
	dpvc(c);
	
	if (this->tokenchars.n + 1 >= this->tokenchars.cap)
	{
		this->tokenchars.cap = this->tokenchars.cap * 2 ?: 1;
		
		dpv(this->tokenchars.cap);
		
		this->tokenchars.chars = realloc(this->tokenchars.chars, this->tokenchars.cap);
		
		assert(this->tokenchars.chars);
	}
	
	this->tokenchars.chars[this->tokenchars.n++] = c;
	
	EXIT;
}

enum token read_token(struct tokenizer* this)
{
	ENTER;
	
	dpvc(this->c);
	
	this->tokenchars.n = 0;
	
	enum tokenizer_state state = ts_start;
	
	while (state >= ts_start)
	{
		state = machine[state][(unsigned) this->c];
		
		if (state > ts_start)
			append(this, this->c);
		else if (state == ts_start)
			this->tokenchars.n = 0;
		
		if (state >= ts_start)
		{
			switch (this->c)
			{
				case '\n': this->line++; break;
				default: break;
			}
			
			read_char(this);
		}
	}
	
	dpvsn(this->tokenchars.chars, this->tokenchars.n);
	
	switch (state)
	{
		case ts_error:
		{
			fprintf(stderr, "zebu: on line %u: "
				"unexpected character after \"%.*s\": '%c' (0x%X)!\n",
				this->line, (int) this->tokenchars.n, this->tokenchars.chars,
				this->c, this->c);
			exit(1);
			break;
		}
		
		case ts_EOF:
			this->token = t_EOF;
			break;
		
		// symbols:
		case ts_dot:
			this->token = t_dot;
			break;
		case ts_vbar:
			this->token = t_vbar;
			break;
		case ts_plus:
			this->token = t_plus;
			break;
		case ts_minus:
			this->token = t_minus;
			break;
		case ts_emark:
			this->token = t_emark;
			break;
		case ts_qmark:
			this->token = t_qmark;
			break;
		case ts_comma:
			this->token = t_comma;
			break;
		case ts_colon:
			this->token = t_colon;
			break;
		case ts_asterisk:
			this->token = t_asterisk;
			break;
		case ts_percent:
			this->token = t_percent;
			break;
		case ts_semicolon:
			this->token = t_semicolon;
			break;
		case ts_gravemark:
			this->token = t_gravemark;
			break;
		case ts_ampersand:
			this->token = t_ampersand;
			break;
		
		// brackets:
		case ts_oparen:
			this->token = t_oparen;
			break;
		case ts_cparen:
			this->token = t_cparen;
			break;
		case ts_osquare:
			this->token = t_osquare;
			break;
		case ts_csquare:
			this->token = t_csquare;
			break;
		
		void escapes()
		{
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
			
			unsigned char* s = this->tokenchars.chars;
			
			unsigned char* w = s, *r = w + 1, *n = w + this->tokenchars.n - 1;
			
			while (r < n)
			{
				dpvc(*r);
				
				if (*r != '\\')
					*w++ = *r++;
				else switch (*++r)
				{
					case 'n': *w++ = '\n', r++; break;
					
					case 't': *w++ = '\t', r++; break;
					
					case '\\': *w++ = '\\', r++; break;
					
					case '\'': *w++ = '\'', r++; break;
					
					case '\"': *w++ = '\"', r++; break;
					
					default:
					{
						dpvc(*r);
						TODO;
						break;
					}
				}
			}
			
			this->tokenchars.n = w - s;
			
			dpvsn(this->tokenchars.chars, this->tokenchars.n);
		}
		
		// literals:
		case ts_character_literal:
			escapes();
			this->token = t_character_literal;
			break;
		case ts_string_literal:
			escapes();
			this->token = t_string_literal;
			break;
		
		case ts_scalar_hashtag:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 1;
			append(this, 0);
			this->token = t_scalar_hashtag;
			break;
		
		case ts_array_hashtag:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 3;
			append(this, 0);
			this->token = t_array_hashtag;
			break;
		
		// identifier:
		case ts_identifier:
			append(this, 0);
			this->token = t_identifier;
			break;
		
		case ts_absolute_path:
			memmove(this->tokenchars.chars, this->tokenchars.chars + 1, this->tokenchars.n);
			this->tokenchars.n -= 2;
			append(this, 0);
			this->token = t_absolute_path;
			break;
		
		default:
		{
			#ifdef DEBUGGING
			TODO;
			#endif
			
			fprintf(stderr, "zebu: on line %u: "
				"internal error in tokenizer.\n", this->line);
			
			exit(1);
			break;
		}
	}
	
	EXIT;
	return this->token;
}

















