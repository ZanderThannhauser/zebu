
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/canonicalize_path.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include "../recursive_parse.h"

#include "include.h"

void read_include_directive(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	const char* root_path,
	const char* curr_path)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	read_token(tokenizer);
	
	const char* prefix;
	
	switch (tokenizer->token)
	{
		case t_string_literal: prefix = curr_path; break;
		
		case t_absolute_path: prefix = root_path; break;
		
		default: TODO; break;
	}
	
	char* path = smalloc(strlen(prefix) + 4 + tokenizer->tokenchars.n + 1);
	
	stpncpy(stpcpy(stpcpy(path, prefix), "/../"), (char*) tokenizer->tokenchars.chars, tokenizer->tokenchars.n)[0] = '\0';
	
	dpvs(path);
	
	char* canon = canonicalize_path(path);
	
	read_token(tokenizer);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* extra_fields: */ extra_fields,
		/* scope: */ scope,
		/* lex: */ lex,
		/* root_path: */ root_path,
		/* path: */ canon);
	
	free(canon);
	free(path);
	
	EXIT;
}











