
#include <assert.h>
#include <stdbool.h>

#include <stdlib.h>

#include <enums/error.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>
#include <yacc/gegex/dotout.h>
#include <yacc/gegex/nfa_to_dfa/nfa_to_dfa.h>

#include "grammar/root.h"
#include "grammar/gbundle.h"

#include "scope/declare/grammar.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/production/root.h"

#include "read_grammar.h"

void read_grammar(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	char* name = sstrdup(tokenizer->tokenchars.chars);
	
	dpvs(name);
	
	// read a colon:
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct gbundle bundle = read_root_production(
		/* tokenizer:  */ tokenizer,
		/* scratchpad: */ scratchpad,
		/* options:    */ options,
		/* scope:      */ scope,
		/* lex:        */ lex);
	
	bundle.end->reduction_point = true;
	
	// nfa to dfa
	struct gegex* dfa_start = gegex_nfa_to_dfa(bundle.start, scratchpad);
	
	#ifdef DEBUGGING
	gegex_dotout(dfa_start, /* optional_end: */ NULL);
	#endif
	
	CHECK;
	
	// add grammar rule to scope
	scope_declare_grammar(scope, name, bundle.start, bundle.end);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	EXIT;
}











