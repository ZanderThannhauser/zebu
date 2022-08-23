
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset(
	struct memory_arena* arena,
	const unsigned char* src, size_t len,
	bool is_complement)
{
	ENTER;
	
	struct charset* this = arena_malloc(arena, sizeof(*this));
	
	this->chars = arena_memdup(arena, src, len);
	this->len = len;
	
	this->is_complement = is_complement;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

