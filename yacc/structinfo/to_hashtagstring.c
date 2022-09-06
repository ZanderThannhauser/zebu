
#include <debug.h>

#include <string/struct.h>

#include "struct.h"
#include "to_hashtagstring.h"

char* structinfo_to_hashtagstring(const struct structinfo* this)
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
		struct structinfo_node* element = node->item;
		
		append("#"), append(element->name->chars);
		
		if (element->kind == sin_grammar_array || element->kind == sin_token_array)
			append("[]");
		
		if (node->next)
			append(", ");
	}
	
	append("");
	
	EXIT;
	return buffer.data;
}











