
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

/*#include "../tokenizer/machines/charset/root.h"*/
#include "../tokenizer/machines/regex/root.h"
#include "../tokenizer/machines/regex/after_highest.h"

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
	struct scope* scope
) {
	struct rbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_character_literal:
			retval = read_character_literal_token_expression(tokenizer, scope);
			break;
		
		case t_string_literal:
			retval = read_string_literal_token_expression(tokenizer, scope);
			break;
		
		case t_identifier:
			retval = read_identifier_token_expression(tokenizer, scope);
			break;
		
		case t_osquare:
			retval = read_square_token_expression(tokenizer, scope);
			break;
		
		case t_dot:
			retval = read_dot_token_expression(tokenizer, scope);
			break;
		
		case t_oparen:
			retval = read_parenthesis_token_expression(tokenizer, scope);
			break;
		
		default:
			TODO;
			break;
	}
	
	read_token(tokenizer, regex_after_highest_machine);
	
	EXIT;
	return retval;
}

















