
#include <string.h>

#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const unsigned char* src, size_t len,
	bool is_complement)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct charset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct charset* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->chars = arena_memdup(arena, src, len);
	#else
	this->chars = memcpy(malloc(len), src, len);
	#endif
	
	this->len = len;
	
	this->is_complement = is_complement;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

