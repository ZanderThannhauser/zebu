
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

/*#include <lex/lookup/add_token.h>*/

/*#include <regex/from_literal.h>*/
/*#include <regex/from_charset.h>*/
/*#include <regex/clone.h>*/
/*#include <regex/dotout.h>*/
/*#include <regex/state/add_lambda_transition.h>*/
/*#include <regex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <regex/dfa_to_nfa.h>*/
/*#include <regex/simplify_dfa/simplify_dfa.h>*/
/*#include <regex/state/struct.h>*/
/*#include <regex/state/free.h>*/
/*#include "../token/root.h"*/

/*#include <gegex/from_token.h>*/
/*#include "gegex/from_empty.h"*/
/*#include <gegex/from_subgrammar.h>*/
/*#include <gegex/dotout.h>*/
/*#include <gegex/clone.h>*/
/*#include <gegex/dfa_to_nfa.h>*/

/*#include "../charset/charset/free.h"*/
/*#include "../charset/root.h"*/

/*#include "../options/struct.h"*/

/*#include "../scope/struct.h"*/
/*#include "../scope/lookup/inline_grammar.h"*/
/*#include "../scope/build_absolute_name.h"*/
/*#include "../scope/translate/grammar.h"*/
/*#include "../scope/pop.h"*/

/*#include "../read_charset.h"*/
/*#include "../read_fragment.h"*/
/*#include "../read_grammar.h"*/

/*#include "../token/rbundle.h"*/
/*#include "../token/root.h"*/

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/token_names.h"

/*#include "../tokenizer/machines/subroot.h"*/
/*#include "../tokenizer/machines/production/root.h"*/
/*#include "../tokenizer/machines/production/after_highest.h"*/
/*#include "../tokenizer/machines/regex/root.h"*/
/*#include "../tokenizer/machines/charset/root.h"*/

#include "highest/square.h"
#include "highest/gravemark.h"
#include "highest/identifier.h"
#include "highest/parenthesis.h"
#include "highest/string_literal.h"
#include "highest/numeric_literal.h"
#include "highest/character_literal.h"

#include "root.h"
#include "0.highest.h"

struct gbundle read_highest_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_oparen:
			retval = read_parenthesis_production(tokenizer, scope, lex);
			break;
		
		case t_osquare:
			retval = read_square_production(tokenizer, scope, lex);
			break;
		
		case t_gravemark:
			retval = read_gravemark_production(tokenizer, scope, lex);
			break;
		
		case t_identifier:
			retval = read_identifier_production(tokenizer, scope, lex);
			break;
		
		case t_octal_literal:
		case t_decimal_literal:
		case t_hexadecimal_literal:
			retval = read_numeric_literal_production(tokenizer, scope, lex);
			break;
		
		case t_string_literal:
			retval = read_string_literal_production(tokenizer, scope, lex);
			break;
		
		case t_character_literal:
			retval = read_character_literal_production(tokenizer, scope, lex);
			break;
		
		default:
		{
			assert(token_names[tokenizer->token]);
			assert(token_names[t_oparen]);
			assert(token_names[t_osquare]);
			assert(token_names[t_gravemark]);
			assert(token_names[t_identifier]);
			assert(token_names[t_string_literal]);
			assert(token_names[t_character_literal]);
			
			fprintf(stderr, "zebu: error while reading grammar rule: "
				"unexpected '%s' token on line %u, expecting '%s', '%s', '%s', '%s', "
				"'%s', '%s'!\n",
				token_names[tokenizer->token],
				tokenizer->line,
				token_names[t_oparen],
				token_names[t_osquare],
				token_names[t_gravemark],
				token_names[t_identifier],
				token_names[t_string_literal],
				token_names[t_character_literal]);
			exit(e_syntax_error);
			break;
		}
	}
	
	EXIT;
	return retval;
}












