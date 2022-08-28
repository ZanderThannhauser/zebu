#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

/*#include <enums/error.h>*/

/*#include <macros/strequals.h>*/

/*#include <arena/malloc.h>*/

/*#include <misc/break_path.h>*/

/*#include "options/struct.h"*/
/*#include "options/dlink.h"*/

/*#include <lex/regex/state/free.h>*/
/*#include <lex/regex/dfa_to_nfa.h>*/
/*#include <lex/regex/state/add_lambda_transition.h>*/

/*#include <yacc/gegex/state/struct.h>*/
/*#include <yacc/gegex/state/free.h>*/
/*#include <yacc/gegex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <yacc/gegex/simplify_dfa/simplify_dfa.h>*/

#include "../tokenizer/struct.h"
/*#include "tokenizer/read_token.h"*/
/*#include "tokenizer/machines/include.h"*/
/*#include "tokenizer/machines/production/root.h"*/
/*#include "tokenizer/machines/misc/semicolon.h"*/
/*#include "tokenizer/machines/misc/colon.h"*/
/*#include "tokenizer/machines/misc/identifier_or_string.h"*/
/*#include "tokenizer/machines/misc/comparision.h"*/
/*#include "tokenizer/machines/regex/root.h"*/

/*#include "scope/declare/grammar.h"*/

/*#include "grammar/root.h"*/

/*#include "token/root.h"*/

/*#include "recursive_parse.h"*/

#include "skip.h"
#include "start.h"
#include "include.h"
#include "token_skip.h"
#include "disambiguate.h"
#include "read_directive.h"

void read_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	const char* const token = (void*) tokenizer->tokenchars.chars;
	
	dpvs(token);
	
	if (strequals(token, "%""start"))
	{
		read_start_directive(pragma_once, tokenizer, options, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""skip"))
	{
		read_skip_directive(pragma_once, tokenizer, options, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""token_skip"))
	{
		read_token_skip_directive(pragma_once, tokenizer, options, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""disambiguate"))
	{
		read_disambiguate_directive(pragma_once, tokenizer, options, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""include"))
	{
		read_include_directive(pragma_once, tokenizer, options, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else
	{
		TODO;
		#if 0
		dpvs(token);
		TODO;
		exit(e_bad_input_file);
		#endif
	}
	
	EXIT;
}














