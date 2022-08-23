
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <arena/memdup.h>

#include "charset/root.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/charset/root.h"

#include "scope/get_arena.h"
#include "scope/declare/charset.h"

#include "read_charset.h"

void read_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_bracketed_identifier);
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct memory_arena* arena = scope_get_arena(scope);
	
	char* name = arena_memdup(arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n + 1);
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, charset_root_machine);
	
	struct charset* charset = read_root_charset(arena, tokenizer, scope);
	
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




















