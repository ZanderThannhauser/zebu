
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <arena/memdup.h>

/*#include <yacc/gegex/state/struct.h>*/
/*#include <yacc/gegex/state/new.h>*/
/*#include <yacc/gegex/nfa_to_dfa/nfa_to_dfa.h>*/
/*#include <yacc/gegex/simplify_dfa/simplify_dfa.h>*/
/*#include <yacc/gegex/state/free.h>*/

#include "grammar/root.h"
#include "grammar/gbundle.h"

#include "scope/declare/inline_grammar.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/production/root.h"

#include "scope/get_arena.h"

#include "read_inline_grammar.h"

void read_inline_grammar(
	#ifdef WITH_ARENAS
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_parenthesised_identifier);
	
	#if WITH_ARENAS
	struct memory_arena* const arena = scope_get_arena(scope);
	char* name = arena_memdup(arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n + 1);
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
		/* grammar_arena: */ arena,
		/* token_arena: */ token_arena,
		#endif
		/* tokenizer:  */ tokenizer,
		/* options:    */ options,
		/* scope:      */ scope,
		/* lex:        */ lex);
	
	scope_declare_inline_grammar(scope, name, bundle.start, bundle.end);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	EXIT;
}











