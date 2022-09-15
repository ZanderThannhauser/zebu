#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

#include <macros/strequals.h>

/*#include <enums/error.h>*/

/*#include <macros/strequals.h>*/

/*#include <arena/malloc.h>*/

/*#include <misc/break_path.h>*/

/*#include "options/struct.h"*/
/*#include "options/dlink.h"*/

/*#include <regex/state/free.h>*/
/*#include <regex/dfa_to_nfa.h>*/
/*#include <regex/state/add_lambda_transition.h>*/

/*#include <gegex/state/struct.h>*/
/*#include <gegex/state/free.h>*/
/*#include <gegex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <gegex/simplify_dfa/simplify_dfa.h>*/

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
#include "read_directive.h"

void read_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
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
		read_start_directive(pragma_once, tokenizer, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""skip"))
	{
		read_skip_directive(pragma_once, tokenizer, scope, lex, absolute_dirfd, relative_dirfd);
	}
	else if (strequals(token, "%""include"))
	{
		read_include_directive(pragma_once, tokenizer, scope, lex, absolute_dirfd, relative_dirfd);
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














