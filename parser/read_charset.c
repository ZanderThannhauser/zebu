
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

int read_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	int error = 0;
	ENTER;
	
	assert(tokenizer->token == t_charset);
	
	char* name = sstrndup(
		/* src: */ tokenizer->tokenchars.chars + 1,
		/* len: */ tokenizer->tokenchars.n - 2);
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, charset_root_machine);
	
	struct charset* charset = read_root_charset(tokenizer, scope);
	
	if (tokenizer->token != t_semicolon)
	{
		TODO;
		exit(1);
	}
	
	scope_declare_charset(scope, name, charset);
	
	read_token(tokenizer, root_machine);
	
	EXIT;
	return error;
}




















