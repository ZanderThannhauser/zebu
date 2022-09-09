
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

/*#include <arena/memdup.h>*/

#include <gegex/state/struct.h>
/*#include <gegex/state/new.h>*/
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa/simplify_dfa.h>
#include <gegex/state/free.h>

#include "production/root.h"
/*#include "grammar/gbundle.h"*/

#include "scope/declare/inline_grammar.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/production/root.h"

/*#include "scope/get_arena.h"*/

#include "read_inline_grammar.h"

void read_inline_grammar(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_parenthesised_identifier);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	// read a colon:
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		/* tokenizer:  */ tokenizer,
		/* options:    */ options,
		/* scope:      */ scope,
		/* lex:        */ lex);
	
	bundle.end->is_reduction_point = true;
	
	struct gegex* nfa_start = bundle.start;
	
	struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
	
	struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
	
	scope_declare_inline_grammar(scope, name, simp_start);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	free_gegex(nfa_start);
	
	free_gegex(dfa_start);
	
	free_string(name);
	
	EXIT;
}











