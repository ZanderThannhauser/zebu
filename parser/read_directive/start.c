
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <string/new.h>
#include <string/free.h>

#include <gegex/struct.h>
#include <gegex/free.h>
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>

#include "../grammar/root.h"

#include "../scope/declare/grammar.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/read_token.h"

#include "start.h"

void read_start_directive(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		assert(token_names[tokenizer->token]);
		assert(token_names[t_colon]);
		
		fprintf(stderr, "zebu: error while reading '%%start' directive: "
			"unexpected '%s', expecting '%s'!\n",
			token_names[tokenizer->token],
			token_names[t_colon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	struct string* name = new_string("$start");
	
	// read a prodution rule:
	struct gbundle nfa = read_root_production(tokenizer, scope, lex);
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	scope_declare_grammar(scope, name, simp);
	
	free_gegex(nfa.start), free_gegex(dfa);
	free_string(name);
	
	EXIT;
}















