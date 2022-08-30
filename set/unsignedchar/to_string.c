
#ifdef DOTOUT

#include <debug.h>

#include <misc/escape.h>

#include "struct.h"
#include "to_string.h"

char* unsignedcharset_to_string(
	const struct unsignedcharset* this,
	bool show_as_complement)
{
	ENTER;
	
	dpv(this->n);
	
	char* buffer = smalloc(1 + 1 + 6 * this->n + 1 + 1);
	
	char* moving = buffer;
	
	*moving++ = '[';
	
	if (show_as_complement)
		*moving++ = '~';
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		unsigned char element = *((unsigned char*) node->item);
		
		char str[10];
		
		escape(str, element);
		
		moving = stpcpy(moving, str);
		
		if (node->next)
			moving = stpcpy(moving, ", ");
	}
	
	*moving++ = ']';
	*moving++ = 0;
	
	EXIT;
	return buffer;
}

#endif












