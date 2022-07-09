
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "read_char.h"
#include "read_token.h"

static void append(struct tokenizer* this, char c)
{
	if (this->tokenchars.n + 1 >= this->tokenchars.cap)
	{
		this->tokenchars.cap = this->tokenchars.cap * 2 ?: 1;
		this->tokenchars.chars = srealloc(this->tokenchars.chars, this->tokenchars.cap);
	}
	
	this->tokenchars.chars[this->tokenchars.n++] = c;
}

enum token read_token(
	struct tokenizer* this,
	const enum tokenizer_state machine[number_of_tokenizer_states][256])
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
			read_char(this);
	}
	
	switch (state)
	{
		case ts_error:
			TODO;
			break;
		
		case ts_EOF:
/*			TODO;*/
			this->token = t_EOF;
			break;
		
		case ts_directive:
			append(this, 0);
			this->token = t_directive;
			dputs("t_directive");
			break;
		
		case ts_start:
			TODO;
			break;
		
		case ts_skipping_comment:
			TODO;
			break;
		
		case ts_after_slash:
			TODO;
			break;
		
		case ts_after_percent:
			TODO;
			break;
		
		case ts_character_literal:
			this->token = t_character_literal;
			dputs("t_character_literal");
			break;
		
		case ts_charset:
			this->token = t_charset;
			dputs("t_charset");
			break;
		
		case ts_fragment:
			this->token = t_fragment;
			dputs("t_fragment");
			break;
		
		case ts_string_literal:
			this->token = t_string_literal;
			dputs("t_string_literal");
			break;
		
		case ts_absolute_path:
			this->token = t_absolute_path;
			dputs("t_absolute_path");
			break;
		
		case ts_relative_path:
			TODO;
/*			this->token = t_relative_path;*/
			break;
		
		case ts_identifier:
			append(this, 0);
			this->token = t_identifier;
			dputs("t_identifier");
			break;
		
		case ts_colon:
			this->token = t_colon;
			dputs("t_colon");
			break;
		
		case ts_plus:
			this->token = t_plus;
			dputs("t_plus");
			break;
		
		case ts_lthan:
			TODO;
			break;
		
		case ts_gthan:
			TODO;
			break;
		
		case ts_comma:
			this->token = t_comma;
			dputs("t_comma");
			break;
		
		case ts_emark:
			this->token = t_emark;
			dputs("t_emark");
			break;
		
		case ts_qmark:
			this->token = t_qmark;
			dputs("t_qmark");
			break;
		
		case ts_ampersand:
			this->token = t_ampersand;
			dputs("t_ampersand");
			break;
		
		case ts_oparen:
			this->token = t_oparen;
			dputs("t_oparen");
			break;
		
		case ts_tilda:
			this->token = t_tilda;
			dputs("t_tilda");
			break;
		
		case ts_dot:
			this->token = t_dot;
			dputs("t_dot");
			break;
		
		case ts_cparen:
			this->token = t_cparen;
			dputs("t_cparen");
			break;
		
		case ts_asterisk:
			this->token = t_asterisk;
			dputs("t_asterisk");
			break;
		
		case ts_osquare:
			this->token = t_osquare;
			dputs("t_osquare");
			break;
		
		case ts_csquare:
			this->token = t_csquare;
			dputs("t_csquare");
			break;
		
		case ts_lthan_eq:
			TODO;
			break;
		
		case ts_gthan_eq:
			TODO;
			break;
		
		case ts_equal_to:
			TODO;
			break;
		
		case ts_vertical_bar:
			this->token = t_vertical_bar;
			dputs("t_vertical_bar");
			break;
		
		case ts_not_equal_to:
			TODO;
			break;
		
		case ts_semicolon:
			this->token = t_semicolon;
			dputs("t_semicolon");
			break;
		
		case ts_gravemark:
			this->token = t_gravemark;
			dputs("t_gravemark");
			break;
		
		case ts_hypen:
			this->token = t_hypen;
			dputs("t_hypen");
			break;
		
		case ts_percent:
			this->token = t_percent;
			dputs("t_percent");
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return this->token;
}

















