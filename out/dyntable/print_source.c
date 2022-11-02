
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "print_source.h"

void dyntable_print_source(struct dyntable* this, const char* prefix, FILE* stream)
{
	ENTER;
	
	fprintf(stream, "const unsigned %s_%s[%u][%u] = {\n", prefix, this->name, this->width + 1, this->height + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct dyntable_node* ele = node->item;
		
		fprintf(stream, "\t[%u][%u] = %u,\n", ele->x, ele->y, ele->v);
	}
	
	fprintf(stream, "};\n");
	
	EXIT;
}







