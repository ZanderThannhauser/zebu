
#include <debug.h>

#include "struct.h"
#include "transition/struct.h"
#include "foreach_transition.h"

void regex_foreach_transition(
	struct regex* this,
	void (*runme)(unsigned char value, struct regex* to)
) {
	ENTER;
	
	for (struct avl_node_t* node = this->transitions->head; node; node = node->next)
	{
		struct regex_transition* const ele = node->item;
		
		runme(ele->value, ele->to);
	}
	
	EXIT;
}
