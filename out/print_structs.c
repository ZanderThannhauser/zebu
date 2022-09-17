
#include <debug.h>

#include <avl/tree_t.h>

#include <yacc/structinfo/print_source.h>

#include "print_structs.h"

void print_structs(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct token" "\n"
		"{" "\n"
			"\t" "unsigned char* data;" "\n"
			"\t" "unsigned len, refcount;" "\n"
		"};" "\n"
		"\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
		structinfo_print_source(node->item, prefix, stream);
	
	EXIT;
}
