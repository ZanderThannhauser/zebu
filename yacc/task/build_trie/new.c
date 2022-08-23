
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct build_trie_task* new_build_trie_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name,
	struct gegex* start,
	struct gegex* mirrorme,
	struct gegex* building,
	unsigned popcount)
{
	ENTER;
	
	struct build_trie_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_build_trie,
		&build_trie_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	this->start = start;
	this->mirrorme = mirrorme;
	this->building = building;
	
	this->popcount = popcount;
	
	EXIT;
	return this;
}

