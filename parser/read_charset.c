
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

#include "charset/root.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "scope/declare/charset.h"

#include "read_charset.h"

void read_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	assert(tokenizer->token == t_bracketed_identifier);
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, charset_root_machine);
	
	charset_t charset = read_root_charset(tokenizer, scope);
	
	scope_declare_charset(scope, name, charset);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	free_string(name);
	#endif
	
	EXIT;
}



















