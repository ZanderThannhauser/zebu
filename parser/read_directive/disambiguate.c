
#include <debug.h>

#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/colon.h>

#include "disambiguate.h"

#if 0
static struct dop read_dop()
{
	TODO;
	#if 0
	read_token(tokenizer, identifier_or_string_machine);
	
	if (tokenizer->token == t_identifier)
	{
		dpvs(tokenizer->tokenchars.chars);
		
		if (strequals(tokenizer->tokenchars.chars, "literal"))
		{
			return (struct dop) {.kind = dk_literal};
		}
		else if (strequals(tokenizer->tokenchars.chars, "regex"))
		{
			return (struct dop) {.kind = dk_regex};
		}
		else
		{
			TODO;
		}
	}
	else if (tokenizer->token == t_string_literal)
	{
		dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
		
		TODO;
		#if 0
		unsigned char* dup = smemdup(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
		
		return (struct dop) {
			.kind = dk_string,
			.s.chars = dup,
			.s.len = tokenizer->tokenchars.n};
		#endif
	}
	else
	{
		TODO;
		exit(1);
	}
	#endif
}
#endif

void read_disambiguate_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	read_token(tokenizer, colon_machine);
	
	TODO;
	#if 0
	struct dop left = read_dop();
	
	read_token(tokenizer, comparision_machine);
	
	int cmp;
	
	switch (tokenizer->token)
	{
		case t_lthan: cmp = -1; break;
		case t_gthan: cmp = +1; break;
		case t_equal_to: cmp = 0; break;
		default: TODO break;
	}
	
	struct dop right = read_dop();
	
	#ifdef WITH_ARENAS
	struct dlink* dlink = arena_malloc(options->arena, sizeof(*dlink));
	#else
	struct dlink* dlink = malloc(sizeof(*dlink));
	#endif
	
	dlink->left = left;
	dlink->cmp = cmp;
	dlink->right = right;
	dlink->next = NULL;
	
	if (options->disambiguatations.head)
	{
		options->disambiguatations.tail->next = dlink;
		options->disambiguatations.tail = dlink;
	}
	else
	{
		options->disambiguatations.head = dlink;
		options->disambiguatations.tail = dlink;
	}
	
	read_token(tokenizer, semicolon_machine);
	#endif
	
	EXIT;
}











