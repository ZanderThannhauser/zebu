
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct build_trie_task* new_build_trie_task(
	struct memory_arena* scratchpad,
	const char* name,
	struct gegex* start,
	struct gegex* mirrorme,
	struct gegex* building,
	unsigned popcount)
{
	ENTER;
	
	struct build_trie_task* this = (void*) new_task(
		tk_build_trie,
		&build_trie_task_inheritance,
		sizeof(*this));
	
	this->scratchpad = scratchpad;
	
	this->name = name;
	this->start = start;
	this->mirrorme = mirrorme;
	this->building = building;
	
	this->popcount = popcount;
	
	EXIT;
	return this;
}

