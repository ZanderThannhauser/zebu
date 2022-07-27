
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <enums/error.h>

#include <debug.h>

#include <memory/sstrndup.h>

#include "charset/root.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/charset/root.h"

#include "scope/declare/charset.h"

#include "read_charset.h"

void read_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_charset);
	
	char* name = sstrndup(
		/* src: */ tokenizer->tokenchars.chars + 1,
		/* len: */ tokenizer->tokenchars.n - 2);
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, charset_root_machine);
	
	struct charset* charset = read_root_charset(tokenizer, scope);
	
	scope_declare_charset(scope, name, charset);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	EXIT;
}




















