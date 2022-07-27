
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void tokenset_to_id_print_source(
	struct tokenset_to_id* this,
	const char* prefix,
	FILE* source, FILE* header)
{
	ENTER;
	
	fprintf(header, "extern const char* %s_grammar_names[%u];\n",
		prefix, this->next + 1);
	
	fprintf(source, "const char* %s_grammar_names[%u] = {\n",
		prefix, this->next + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct tokenset_to_id_node* const ele = node->item;
		
		if (!ele->is_tokenset)
		{
			fprintf(source, "\t[%u] = \"%s\",\n", ele->id, ele->grammar);
		}
	}
	
	fprintf(source, "};\n");
	
	EXIT;
}

