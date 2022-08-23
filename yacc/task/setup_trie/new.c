
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct setup_trie_task* new_setup_trie_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* node,
	const char* name)
{
	ENTER;
	
	struct setup_trie_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_setup_trie,
		&setup_trie_task_inheritance,
		sizeof(*this));
	
	this->node = node;
	this->name = name;
	
	this->built_name = NULL;
	
	EXIT;
	return this;
}

