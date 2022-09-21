
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

#include <gegex/struct.h>
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include "grammar/root.h"

#include "scope/declare/grammar.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "read_grammar.h"

void read_grammar(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	TODO;
	#if 0
	assert(tokenizer->token == t_identifier);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	dpvs(name);
	
	// read a colon:
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		/* tokenizer:     */ tokenizer,
		/* scope:         */ scope,
		/* lex:           */ lex);
	
	bundle.end->is_reduction_point = true;
	
	struct gegex* nfa_start = bundle.start;
	
	struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
	
	struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
	
	scope_declare_grammar(scope, name, simp_start);
	
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
	#endif
	
	EXIT;
}










