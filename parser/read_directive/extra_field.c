
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_user_defined_field.h>
#include <yacc/structinfo/free.h>

#include <named/structinfo/new.h>

#include "../tokenizer/struct.h"
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
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		TODO;
		exit(1);
	}
	
	struct string* grammar = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_comma)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_string_literal)
	{
		TODO;
		exit(1);
	}
	
	struct string* type = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_comma)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		TODO;
		exit(1);
	}
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	struct string* destructor = NULL;
	
	if (tokenizer->token == t_comma)
	{
		read_token(tokenizer);
		
		if (tokenizer->token != t_identifier)
		{
			TODO;
			exit(1);
		}
		
		destructor = new_string_from_tokenchars(tokenizer);
		
		read_token(tokenizer);
		
		if (tokenizer->token != t_oparen)
		{
			TODO;
			exit(1);
		}
		
		read_token(tokenizer);
		
		if (tokenizer->token != t_cparen)
		{
			TODO;
			exit(1);
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
		TODO;
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
		TODO;
		exit(1);
	}
	
	free_string(grammar);
	free_string(type);
	free_string(name);
	free_string(destructor);
	
	EXIT;
}


















