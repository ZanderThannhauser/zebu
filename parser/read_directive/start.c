
#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/colon.h>
#include <parser/tokenizer/machines/production/root.h>

#include <gegex/state/struct.h>
#include <gegex/state/free.h>
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa/simplify_dfa.h>

#include "../production/root.h"

#include "../scope/declare/grammar.h"

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
	
	struct string* name = new_string("$start");
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		/*     tokenizer: */ tokenizer,
		/*       options: */ options,
		/*         scope: */ scope,
		/*           lex: */ lex);
	
	bundle.end->is_reduction_point = true;
	
	struct gegex* nfa_start = bundle.start;
	
	struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
	
	struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
	
	scope_declare_grammar(scope, name, simp_start);
	
	free_gegex(nfa_start), free_gegex(dfa_start);
	
	free_string(name);
	
	EXIT;
}















