
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void dynvector_print_source(
	struct dynvector* this,
	FILE* source,
	FILE* header)
{
	ENTER;
	
	dpvs(this->name);
	
	fprintf(header, "extern const unsigned %s[%u];\n", this->name, this->length + 1);
	
	fprintf(source, "const unsigned %s[%u] = {\n", this->name, this->length + 1);
	
	for (struct avl_node_t* node = this->list->head; node; node = node->next)
	{
		struct dynvector_node* ele = node->item;
		
		fprintf(source, "\t[%u] = %u,\n", ele->i, ele->v);
	}
	
	fprintf(source, "};\n");
	
	EXIT;
}

