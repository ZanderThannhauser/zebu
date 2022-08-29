
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <debug.h>

/*#include <lex/lookup/add_token.h>*/

/*#include <memory/arena/malloc.h>*/

/*#include <lex/regex/from_literal.h>*/
/*#include <lex/regex/from_charset.h>*/
/*#include <lex/regex/clone.h>*/
/*#include <lex/regex/dotout.h>*/
/*#include <lex/regex/state/add_lambda_transition.h>*/
/*#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <lex/regex/dfa_to_nfa.h>*/
/*#include <lex/regex/simplify_dfa/simplify_dfa.h>*/
/*#include <lex/regex/state/struct.h>*/
/*#include <lex/regex/state/free.h>*/
/*#include "../token/root.h"*/

/*#include <yacc/gegex/from_token.h>*/
/*#include "gegex/from_empty.h"*/
/*#include <yacc/gegex/from_subgrammar.h>*/
/*#include <yacc/gegex/dotout.h>*/
/*#include <yacc/gegex/clone.h>*/
/*#include <yacc/gegex/dfa_to_nfa.h>*/

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
/*#include "../tokenizer/read_token.h"*/

/*#include "../tokenizer/machines/subroot.h"*/
/*#include "../tokenizer/machines/production/root.h"*/
/*#include "../tokenizer/machines/production/after_highest.h"*/
/*#include "../tokenizer/machines/regex/root.h"*/
/*#include "../tokenizer/machines/charset/root.h"*/

#include "highest/character_literal.h"
#include "highest/string_literal.h"
#include "highest/parenthesis.h"
#include "highest/identifier.h"
#include "highest/gravemark.h"
#include "highest/square.h"

#include "root.h"
#include "0.highest.h"

struct gbundle read_highest_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	switch (tokenizer->token)
	{
		case t_oparen:
			retval = read_parenthesis_production(tokenizer, options, scope, lex);
			break;
		
		case t_character_literal:
			retval = read_character_literal_production(tokenizer, options, scope, lex);
			break;
		
		case t_string_literal:
			retval = read_string_literal_production(tokenizer, options, scope, lex);
			break;
		
		case t_osquare:
			retval = read_square_production(tokenizer, options, scope, lex);
			break;
		
		case t_gravemark:
			retval = read_gravemark_production(tokenizer, options, scope, lex);
			break;
		
		case t_identifier:
			retval = read_identifier_production(tokenizer, options, scope, lex);
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return retval;
}












