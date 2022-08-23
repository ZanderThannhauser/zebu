
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct gegex_to_trie* new_gegex_to_trie(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* gegex,
	const char* trie)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex_to_trie* this = arena_malloc(arena, sizeof(*this));
	#else
	struct gegex_to_trie* this = malloc(sizeof(*this));
	#endif
	
	this->gegex = gegex;
	this->trie = trie;
	
	EXIT;
	return this;
}

