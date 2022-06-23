
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
	enum tokenizer_state machine[number_of_tokenizer_states][256])
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
		
		case ts_character_literal: this->token = t_character_literal; break;
		
		case ts_charset: this->token = t_charset; break;
		
		case ts_fragment: this->token = t_fragment; break;
		
		case ts_string_literal: this->token = t_string_literal; break;
		
		case ts_absolute_path: this->token = t_absolute_path; break;
		
		case ts_relative_path:
			TODO;
/*			this->token = t_relative_path;*/
			break;
		
		case ts_identifier: append(this, 0); this->token = t_identifier; break;
		
		case ts_colon: this->token = t_colon; break;
		
		case ts_plus: this->token = t_plus; break;
		
		case ts_lthan:
			TODO;
			break;
		
		case ts_gthan:
			TODO;
			break;
		
		case ts_emark: this->token = t_emark; break;
		
		case ts_qmark: this->token = t_qmark; break;
		
		case ts_ampersand: this->token = t_ampersand; break;
		
		case ts_oparen: this->token = t_oparen; break;
		
		case ts_tilda: this->token = t_tilda; break;
		
		case ts_dot: this->token = t_dot; break;
		
		case ts_cparen: this->token = t_cparen; break;
		
		case ts_asterisk: this->token = t_asterisk; break;
		
		case ts_osqaure: this->token = t_osquare; break;
		
		case ts_csqaure: this->token = t_csquare; break;
		
		case ts_lthan_eq:
			TODO;
			break;
		
		case ts_gthan_eq:
			TODO;
			break;
		
		case ts_equal_to:
			TODO;
			break;
		
		case ts_vertical_bar: this->token = t_vertical_bar; break;
		
		case ts_not_equal_to:
			TODO;
			break;
		
		case ts_semicolon: this->token = t_semicolon; break;
		
		case ts_gravemark: this->token = t_gravemark; break;
		
		case ts_hypen: this->token = t_hypen; break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return this->token;
}

















