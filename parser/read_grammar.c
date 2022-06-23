
#include <debug.h>

#include <memory/sstrdup.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/production/root.h"

#include "production/gegex/state/struct.h"
#include "production/gegex/state/new.h"
#include "production/root.h"

#include "scope/declare/grammar.h"

#include "read_grammar.h"

void read_grammar(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	char* name = sstrdup(tokenizer->tokenchars.chars);
	
	dpvs(name);
	
	// create "start" grammar state:
	struct gegex* start = new_gegex(scratchpad);
	
	// read a colon:
	read_token(tokenizer, colon_machine);
	
	// prep production-rule reader:
	read_token(tokenizer, production_root_machine);
	
	// read a prodution rule:
	struct bundle bundle = read_root_production(
		/* tokenizer: */ tokenizer,
		/* scratchpad: */ scratchpad,
		/* scope: */ scope,
		/* lex: */ lex);
	
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











