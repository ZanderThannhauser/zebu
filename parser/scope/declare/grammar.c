
#if 0
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <named/grammar/new.h>

#include <avl/insert.h>

#include <arena/strdup.h>
#include <arena/malloc.h>

#include "../struct.h"

#include "grammar.h"

void scope_declare_grammar(
	struct scope* this,
	const char* name,
	struct gegex* grammar)
{
	ENTER;
	
	dpvs(name);
	
	char* full;
	
	size_t len = strlen(name);
	
	if (this->prefix.n)
	{
		#ifdef WITH_ARENAS
		full = arena_malloc(
			this->grammar_arena,
		#else
		full = malloc(
		#endif
			this->prefix.n + 1 + len + 1);
		
		char* moving = full;
		
		memcpy(moving, this->prefix.chars, this->prefix.n), moving += this->prefix.n;
		
		*moving++ = '.';
		
		memcpy(moving, name, len), moving += len;
		
		*moving++ = '\0';
	}
	else
	{
		#ifdef WITH_ARENAS
		full = arena_strdup(this->grammar_arena, name);
		#else
		full = strdup(name);
		#endif
	}
	
	dpvs(full);
	
	#ifdef WITH_ARENAS
	avl_insert(this->grammar, new_named_grammar(this->grammar_arena, full, grammar));
	#else
	avl_insert(this->grammar, new_named_grammar(full, grammar));
	#endif
	
	EXIT;
}















#endif
