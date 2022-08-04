
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct setup_trie_task* new_setup_trie_task(
	struct memory_arena* scratchpad,
	struct gegex* node,
	const char* name)
{
	ENTER;
	
	struct setup_trie_task* this = (void*) new_task(
		tk_setup_trie,
		&setup_trie_task_inheritance,
		sizeof(*this));
	
	this->scratchpad = scratchpad;
	this->node = node;
	this->name = name;
	
	this->built_name = NULL;
	
	EXIT;
	return this;
}

