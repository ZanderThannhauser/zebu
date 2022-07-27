
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void dyntable_print_source(
	struct dyntable* this,
	FILE* source,
	FILE* header)
{
	ENTER;
	
	dpvs(this->name);
	
	fprintf(header, "extern const unsigned %s[%u][%u];\n",
		this->name, this->width + 1, this->height + 1);
	
	fprintf(source, "const unsigned %s[%u][%u] = {\n",
		this->name, this->width + 1, this->height + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct dyntable_node* ele = node->item;
		
		fprintf(source, "\t[%u][%u] = %u,\n", ele->x, ele->y, ele->v);
	}
	
	fprintf(source, "};\n");
	
	EXIT;
}

