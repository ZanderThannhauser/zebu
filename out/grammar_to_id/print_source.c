
#if 0
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void grammar_to_id_print_source(
	struct grammar_to_id* this,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, "const char* grammar_names[%u] = {\n", this->next + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct grammar_to_id_node* ele = node->item;
		
		fprintf(stream, "\t[%u] = \"%s\",\n", ele->id, ele->grammar);
	}
	
	fprintf(stream, "};\n");
		
	EXIT;
}

#endif
