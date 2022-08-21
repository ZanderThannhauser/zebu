
#include <debug.h>

#include <set/of_gegexes/clone.h>

#include "struct.h"
#include "new.h"

struct gegex_mapping* new_gegex_mapping(struct gegexset* set, struct gegex* state)
{
	ENTER;
	
	TODO;
	#if 0
	struct gegex_mapping* this = smalloc(sizeof(*this));
	
	this->original_states = gegexset_clone(set);
	this->combined_state = state;
	
	EXIT;
	return this;
	#endif
}

