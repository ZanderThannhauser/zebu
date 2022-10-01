
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

#include <macros/strequals.h>

#include <enums/error.h>

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

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

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

#include "read_directive.h"

#include "read_directive/skip.h"
#include "read_directive/start.h"
#include "read_directive/include.h"
#include "read_directive/extra_field.h"

void read_directive(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	const char* root_path,
	const char* curr_path)
{
	ENTER;
	
	assert(tokenizer->token == t_percent);
	
	read_token(tokenizer);
	
	const char* const token = (void*) tokenizer->tokenchars.chars;
	
	dpvs(token);
	
	if (strequals(token, "start"))
	{
		read_start_directive(tokenizer, scope, lex);
	}
	else if (strequals(token, "skip"))
	{
		read_skip_directive(tokenizer, scope, lex);
	}
	else if (strequals(token, "include"))
	{
		read_include_directive(pragma_once, extra_fields, tokenizer, scope, lex, root_path, curr_path);
	}
	else if (strequals(token, "extra_field"))
	{
		read_extra_field_directive(tokenizer, extra_fields);
	}
	else
	{
		fprintf(stderr, "zebu: unknown directive '%s'!\n", token);
		exit(e_syntax_error);
	}
	
	EXIT;
}














