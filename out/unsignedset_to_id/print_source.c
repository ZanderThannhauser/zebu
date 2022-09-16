
#include <stdlib.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <set/unsigned/to_string.h>

#include "struct.h"
#include "print_source.h"

void unsignedset_to_id_print_source(
	struct unsignedset_to_id* this,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, "static const char* %s_token_names[%u] = {\n",
		prefix, this->next + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct unsignedset_to_id_node* const ele = node->item;
		
		char* label = unsignedset_to_string(ele->unsignedset);
		
		fprintf(stream, "\t[%u] = \"%s\",\n", ele->id, label);
		
		free(label);
	}
	
	fprintf(stream, "};\n");
	
	EXIT;
}











