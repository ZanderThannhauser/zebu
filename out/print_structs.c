
#include <debug.h>

#include <avl/tree_t.h>

#include <named/structinfo/struct.h>

#include <yacc/structinfo/print_source.h>

#include "print_structs.h"

void print_structs(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct %s_token" "\n"
		"{" "\n"
			"\t" "unsigned char* data;" "\n"
			"\t" "unsigned len, refcount;" "\n"
		"};" "\n"
		"\n"
	"", prefix);
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct named_structinfo* ele = node->item;
		structinfo_print_source(ele->structinfo, ele->name, prefix, stream);
	}
	
	EXIT;
}
