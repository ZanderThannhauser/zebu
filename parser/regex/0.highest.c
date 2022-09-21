
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/token_names.h"

/*#include "../scope/lookup/token.h"*/

/*#include "../charset/root.h"*/

/*#include <regex/dotout.h>*/
/*#include <regex/clone.h>*/
/*#include <regex/from_dot.h>*/
/*#include <regex/from_charset.h>*/
/*#include <regex/from_literal.h>*/

#include "highest/character_literal.h"
#include "highest/string_literal.h"
#include "highest/parenthesis.h"
#include "highest/identifier.h"
#include "highest/square.h"
#include "highest/dot.h"

#include "root.h"
#include "0.highest.h"

struct rbundle read_highest_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_dot:
			retval = read_dot_token_expression(tokenizer, scope);
			break;
		
		case t_oparen:
			retval = read_parenthesis_token_expression(tokenizer, scope);
			break;
		
		case t_osquare:
			retval = read_square_token_expression(tokenizer, scope);
			break;
		
		case t_identifier:
			retval = read_identifier_token_expression(tokenizer, scope);
			break;
		
		case t_string_literal:
			retval = read_string_literal_token_expression(tokenizer, scope);
			break;
		
		case t_character_literal:
			retval = read_character_literal_token_expression(tokenizer, scope);
			break;
		
		default:
		{
			dpv(tokenizer->token);
			
			assert(token_names[tokenizer->token]);
			assert(token_names[t_dot]);
			assert(token_names[t_oparen]);
			assert(token_names[t_osquare]);
			assert(token_names[t_identifier]);
			assert(token_names[t_string_literal]);
			assert(token_names[t_character_literal]);
			
			fprintf(stderr, "zebu: error while reading regular expression: "
				"unexpected '%s' token on line %u, expecting '%s', '%s', '%s', '%s', "
				"'%s', '%s'!\n",
				token_names[tokenizer->token],
				tokenizer->line,
				token_names[t_dot],
				token_names[t_oparen],
				token_names[t_osquare],
				token_names[t_identifier],
				token_names[t_string_literal],
				token_names[t_character_literal]);
			
			exit(e_syntax_error);
			break;
		}
	}
	
	read_token(tokenizer);
	
	EXIT;
	return retval;
}

















