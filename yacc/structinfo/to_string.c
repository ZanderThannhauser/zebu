
#include <assert.h>
#include <string.h>
#include <stddef.h>

#include <debug.h>

#include <string/struct.h>

#include <memory/srealloc.h>

#include <avl/foreach.h>

#include "node.h"
#include "struct.h"
#include "to_string.h"

char* structinfo_to_string(struct structinfo* this)
{
	ENTER;
	
	TODO;
	#if 0
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
	
	append("struct "), append(" {\\l");
	
	avl_tree_foreach(this->tree, ({
		void runme(void* ptr)
		{
			struct structinfo_node* node = ptr;
			
			switch (node->type)
			{
				case snt_token_scalar:
					append("struct token* "), append(node->name->chars), append(";\\l");
					break;
				
				case snt_token_array:
					append("struct token* "), append(node->name->chars), append("[];\\l");
					break;
				
				case snt_grammar_scalar:
					append("struct "), append(node->grammar->chars);
					append("* "), append(node->name->chars), append(";\\l");
					break;
				
				case snt_grammar_array:
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
	#endif
}















