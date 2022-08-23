
#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct charset* new_charset_from_range(
	struct memory_arena* arena,
	unsigned char low, unsigned char high)
{
	ENTER;
	
	dpvc(low);
	dpvc(high);
	
	struct charset* this = arena_malloc(arena, sizeof(*this));
	
	assert(high > low);
	
	this->len = (high - low) + 1;
	
	dpv(this->len);
	
	unsigned char* chars = this->chars = arena_malloc(arena, this->len);
	
	for (unsigned char moving = low; moving <= high; ) *chars++ = moving++;
	
	dpvsn(this->chars, this->len);
	
	this->is_complement = false;
	
	this->arena = arena;
	
	EXIT;
	return this;
}














