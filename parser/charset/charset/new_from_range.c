
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset_from_range(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	unsigned char low, unsigned char high)
{
	ENTER;
	
	dpvc(low);
	dpvc(high);
	
	#ifdef WITH_ARENAS
	struct charset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct charset* this = malloc(sizeof(*this));
	#endif
	
	assert(high > low);
	
	this->len = (high - low) + 1;
	
	dpv(this->len);
	
	#ifdef WITH_ARENAS
	unsigned char* chars = this->chars = arena_malloc(arena, this->len);
	#else
	unsigned char* chars = this->chars = malloc(this->len);
	#endif
	
	for (unsigned char moving = low; moving <= high; ) *chars++ = moving++;
	
	dpvsn(this->chars, this->len);
	
	this->is_complement = false;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}














