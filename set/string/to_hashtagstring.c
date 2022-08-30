
#include <debug.h>

#include "struct.h"
#include "to_hashtagstring.h"

char* stringset_to_hashtagstring(const struct stringset* this)
{
	ENTER;
	
	struct {
		char* data;
		size_t n, cap;
	} buffer = {};
	
	void append(char* str)
	{
		size_t len = strlen(str) ?: 1;
		
		while (buffer.n + len > buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, sizeof(*buffer.data) * buffer.cap);
		}
		
		memcpy(buffer.data + buffer.n, str, len);
		
		buffer.n += len;
	}
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		char* element = node->item;
		
		append("#"), append(element);
		
		if (node->next)
		{
			append(", ");
		}
	}
	
	append("");
	
	EXIT;
	return buffer.data;
}

