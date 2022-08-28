
#include <debug.h>

#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/colon.h>
#include <parser/tokenizer/machines/production/root.h>

#include "../production/root.h"

#include "start.h"

void read_start_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		/*     tokenizer: */ tokenizer,
		/*       options: */ options,
		/*         scope: */ scope,
		/*           lex: */ lex);
	
	TODO;
	#if 0
	bundle.end->is_reduction_point = true;
	
	struct gegex* nfa_start = bundle.start;
	
	// nfa to dfa
	#ifdef WITH_ARENAS
	struct gegex* dfa_start = gegex_nfa_to_dfa(grammar_arena, nfa_start);
	#else
	struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
	#endif
	
	// simplify
	#ifdef WITH_ARENAS
	struct gegex* simp_start = gegex_simplify_dfa(grammar_arena, dfa_start);
	#else
	struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
	#endif
	
	// add grammar rule to scope
	scope_declare_grammar(scope, "(start)", simp_start);
	
	free_gegex(nfa_start), free_gegex(dfa_start);
	#endif
	EXIT;
}

		
