
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "union.h"

struct charset* charset_union(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct charset* a,
	const struct charset* b,
	bool is_complement)
{
	ENTER;
	
	size_t n = 0;
	
	#ifdef WITH_ARENAS
	unsigned char* chars = arena_malloc(arena, sizeof(*chars) * (a->len + b->len));
	#else
	unsigned char* chars = malloc(sizeof(*chars) * (a->len + b->len));
	#endif
	
	size_t a_i = 0, a_n = a->len;
	size_t b_i = 0, b_n = b->len;
	
	while (a_i < a_n && b_i < b_n)
	{
		char a_ele = a->chars[a_i], b_ele = b->chars[b_i];
		
		if (a_ele < b_ele)
			chars[n++] = a_ele, a_i++;
		else if (a_ele > b_ele)
			chars[n++] = b_ele, b_i++;
		else
			chars[n++] = a_ele, a_i++, b_i++;
	}
	
	while (a_i < a_n)
		chars[n++] = a->chars[a_i++];
	
	while (b_i < b_n)
		chars[n++] = b->chars[b_i++];
	
	#ifdef WITH_ARENAS
	struct charset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct charset* this = malloc(sizeof(*this));
	#endif
	
	this->chars = chars;
	this->len = n;
	
	this->is_complement = is_complement;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}




















