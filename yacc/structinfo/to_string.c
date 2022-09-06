
#include <debug.h>

#include <avl/foreach.h>

#include "struct.h"
#include "to_string.h"

char* structinfo_to_string(struct structinfo* this)
{
	ENTER;
	
	struct {
		char* data;
		size_t n, cap;
	} buffer = {};
	
	void append(const char* string)
	{
		size_t len = strlen(string);
		while (buffer.n + len >= buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, buffer.cap);
		}
		memcpy(buffer.data + buffer.n, string, len + 1);
		buffer.n += len;
	}
	
	append("struct "), append(this->name->chars), append(" {\\l");
	
	avl_tree_foreach(this->tree, ({
		void runme(void* ptr)
		{
			struct structinfo_node* node = ptr;
			
			dpvs(node->name->chars);
			
			switch (node->kind)
			{
				case sin_token_scalar:
					append("struct token* "), append(node->name->chars), append(";\\l");
					break;
				
				case sin_token_array:
					TODO;
					break;
				
				case sin_grammar_scalar:
					append("struct "), append(node->grammar->chars);
					append("* "), append(node->name->chars), append(";\\l");
					break;
				
				case sin_grammar_array:
					append("struct "), append(node->grammar->chars);
					append("* "), append(node->name->chars), append("[];\\l");
					break;
				
				default:
					TODO;
					break;
			}
		}
		runme;
	}));
	
	append("};\\l");
	
	dpvs(buffer.data);
	
	EXIT;
	return buffer.data;
}















