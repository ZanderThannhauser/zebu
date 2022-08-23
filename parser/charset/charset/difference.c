
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "difference.h"

struct charset* charset_difference(
	struct memory_arena* arena,
	const struct charset* a,
	const struct charset* b,
	bool is_complement)
{
	ENTER;
	
	size_t n = 0;
	
	unsigned char* chars = arena_malloc(arena, sizeof(*chars) * a->len);
	
	size_t a_i = 0, a_n = a->len;
	size_t b_i = 0, b_n = b->len;
	
	while (a_i < a_n && b_i < b_n)
	{
		unsigned char a_ele = a->chars[a_i], b_ele = b->chars[b_i];
		
		if (a_ele < b_ele)
			chars[n++] = a_ele, a_i++;
		else if (a_ele > b_ele)
			b_i++;
		else
			a_i++, b_i++;
	}
	
	while (a_i < a_n)
		chars[n++] = a->chars[a_i++];
	
	struct charset* this = arena_malloc(arena, sizeof(*this));
	
	this->chars = chars;
	this->len = n;
	
	this->is_complement = is_complement;
	
	this->arena = arena;
	
	EXIT;
	return this;
}




















