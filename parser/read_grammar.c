
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

/*#include <enums/error.h>*/

/*#include <yacc/gegex/state/struct.h>*/
/*#include <yacc/gegex/state/new.h>*/
/*#include <yacc/gegex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <yacc/gegex/simplify_dfa/simplify_dfa.h>*/
/*#include <yacc/gegex/state/free.h>*/

/*#include "grammar/root.h"*/
/*#include "grammar/gbundle.h"*/

/*#include "scope/declare/grammar.h"*/

/*#include "tokenizer/struct.h"*/
/*#include "tokenizer/read_token.h"*/
/*#include "tokenizer/machines/misc/colon.h"*/
/*#include "tokenizer/machines/production/root.h"*/

#include "read_grammar.h"

void read_grammar(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	TODO;
	#if 0
	assert(tokenizer->token == t_identifier);
	
	#ifdef WITH_ARENAS
	char* name = arena_memdup(grammar_arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n + 1);
	#else
	char* name = strdup(tokenizer->tokenchars.chars);
	#endif
	
	dpvs(name);
	
	// read a colon:
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		#ifdef WITH_ARENAS
		/* grammar_arena: */ grammar_arena,
		/* token_arena:   */ token_arena,
		#endif
		/* tokenizer:     */ tokenizer,
		/* options:       */ options,
		/* scope:         */ scope,
		/* lex:           */ lex);
	
	bundle.end->is_reduction_point = true;
	
	struct gegex* nfa_start = bundle.start;
	
	#ifdef WITH_ARENAS
	struct gegex* dfa_start = gegex_nfa_to_dfa(grammar_arena, nfa_start);
	struct gegex* simp_start = gegex_simplify_dfa(grammar_arena, dfa_start);
	#else
	struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
	struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
	#endif
	
	// add grammar rule to scope
	scope_declare_grammar(scope, name, simp_start);
	
	free_gegex(nfa_start), free_gegex(dfa_start);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	#endif
	
	EXIT;
}










