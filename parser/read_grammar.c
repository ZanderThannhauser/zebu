
#include <stdio.h>
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
#include "tokenizer/token_names.h"

#include "read_grammar.h"

void read_grammar(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	dpvs(name);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_colon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	// read a prodution rule:
	struct gbundle nfa = read_root_production(tokenizer, scope, lex);
	
	nfa.accepts->accepts = true;
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	scope_declare_grammar(scope, name, simp);
	
	free_gegex(nfa.start);
	
	free_gegex(dfa);
	
	free_string(name);
	
	EXIT;
}










