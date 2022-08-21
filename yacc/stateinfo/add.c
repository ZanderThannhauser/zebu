
#include <debug.h>

#include "node/new.h"

#include "struct.h"
#include "add.h"

void yacc_stateinfo_add(
	struct yacc_stateinfo* this,
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads)
{
	ENTER;
	
	TODO;
	#if 0
	struct yacc_stateinfo_node* node = new_yacc_stateinfo_node(state, grammar, lookaheads);
	
	safe_avl_insert(this->tree, node);
	#endif
	
	EXIT;
}

