
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <string/new.h>
#include <string/free.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_user_defined_field.h>
#include <yacc/structinfo/free.h>

#include <named/structinfo/struct.h>
#include <named/structinfo/new.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/token_names.h"
#include "../tokenizer/read_token.h"

#include "extra_field.h"

void read_extra_field_directive(
	struct tokenizer* tokenizer,
	struct avl_tree_t* extra_fields)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
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
	
	if (tokenizer->token != t_identifier)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_identifier]);
		exit(e_syntax_error);
	}
	
	struct string* grammar = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_comma)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_comma]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_string_literal)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_string_literal]);
		exit(e_syntax_error);
	}
	
	struct string* type = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_comma)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_comma]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_identifier]);
		exit(e_syntax_error);
	}
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	struct string* destructor = NULL;
	
	if (tokenizer->token == t_comma)
	{
		read_token(tokenizer);
		
		if (tokenizer->token != t_identifier)
		{
			fprintf(stderr, "zebu: encountered syntax error on line %u: "
				"unexpected '%s', expecting '%s'!\n",
				tokenizer->line,
				token_names[tokenizer->token],
				token_names[t_identifier]);
			exit(e_syntax_error);
		}
		
		destructor = new_string_from_tokenchars(tokenizer);
		
		read_token(tokenizer);
		
		if (tokenizer->token != t_oparen)
		{
			fprintf(stderr, "zebu: encountered syntax error on line %u: "
				"unexpected '%s', expecting '%s'!\n",
				tokenizer->line,
				token_names[tokenizer->token],
				token_names[t_oparen]);
			exit(e_syntax_error);
		}
		
		read_token(tokenizer);
		
		if (tokenizer->token != t_cparen)
		{
			fprintf(stderr, "zebu: encountered syntax error on line %u: "
				"unexpected '%s', expecting '%s'!\n",
				tokenizer->line,
				token_names[tokenizer->token],
				token_names[t_cparen]);
			exit(e_syntax_error);
		}
		
		read_token(tokenizer);
	}
	
	dpvs(grammar);
	dpvs(type);
	dpvs(name);
	
	if (destructor)
	{
		dpvs(destructor);
	}
	
	struct avl_node_t* node = avl_search(extra_fields, &grammar);
	
	if (node)
	{
		struct named_structinfo* nstructinfo = node->item;
		
		structinfo_add_user_defined_field(nstructinfo->structinfo, type, name, destructor);
	}
	else
	{
		struct structinfo* structinfo = new_structinfo();
		
		structinfo_add_user_defined_field(structinfo, type, name, destructor);
		
		avl_insert(extra_fields, new_named_structinfo(grammar, structinfo));
		
		free_structinfo(structinfo);
	}
	
	if (tokenizer->token != t_semicolon)
	{
		fprintf(stderr, "zebu: encountered syntax error on line %u: "
			"unexpected '%s', expecting '%s'!\n",
			tokenizer->line,
			token_names[tokenizer->token],
			token_names[t_semicolon]);
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	free_string(grammar);
	free_string(type);
	free_string(name);
	free_string(destructor);
	
	EXIT;
}


















