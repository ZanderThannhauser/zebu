
#include <stdio.h>
#include <string.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <memory/srealloc.h>

#include "struct.h"

#include "to_string.h"

char* unsignedset_to_string(const struct unsignedset* this)
{
	ENTER;
	
	struct {
		char* data;
		unsigned n, cap;
	} buffer = {};
	
	void append(const char* str)
	{
		unsigned len = strlen(str);
		
		while (buffer.n + len >= buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, buffer.cap);
		}
		
		memcpy(buffer.data + buffer.n, str, len + 1);
		buffer.n += len;
	}
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		unsigned ele = *(unsigned*) node->item;
		
		dpv(ele);
		
		char buffer[40];
		
		sprintf(buffer, "%u", ele);
		
		append(buffer);
		
		if (node->next)
			append(", ");
	}
	
	dpvs(buffer.data);
	
	EXIT;
	return buffer.data;
}

