
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct gegex_to_trie* new_gegex_to_trie(
	struct memory_arena* arena,
	struct gegex* gegex,
	const char* trie)
{
	ENTER;
	
	struct gegex_to_trie* this = arena_malloc(arena, sizeof(*this));
	
	this->gegex = gegex;
	this->trie = trie;
	
	EXIT;
	return this;
}

