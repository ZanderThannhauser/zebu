
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void dynvector_print_source(
	struct dynvector* this,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	dpvs(this->name);
	
	fprintf(stream, "const unsigned %s_%s[%u] = {\n", prefix, this->name, this->length + 1);
	
	for (struct avl_node_t* node = this->list->head; node; node = node->next)
	{
		struct dynvector_node* ele = node->item;
		
		fprintf(stream, "\t[%u] = %u,\n", ele->i, ele->v);
	}
	
	fprintf(stream, "};\n");
	
	EXIT;
}














