
#include <debug.h>

#include <avl/tree_t.h>

#include <set/string/new.h>
#include <set/string/free.h>

#include <yacc/structinfo/print_source.h>

#include "print_structs.h"

void print_structs(
	struct avl_tree_t* structinfos,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct token" "\n"
		"{" "\n"
			"unsigned char* data;" "\n"
			"unsigned len, refcount;" "\n"
		"};" "\n"
	"");
	
	struct stringset* done = new_stringset();
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
		structinfo_print_source(node->item, done, stream);
	
	free_stringset(done);
	
	EXIT;
}
