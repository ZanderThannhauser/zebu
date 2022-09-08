
#include <debug.h>

#include <yacc/structinfo/struct.h>

#include "print_inc_functions.h"

void print_inc_functions(
	struct avl_tree_t* structinfos,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct token* inc_token(struct token* this)" "\n"
		"{" "\n"
			"\t" "if (this) this->refcount++;" "\n"
			"\t" "return this;" "\n"
		"}" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		const char* type = ele->name->chars;
		
		fprintf(stream, ""
			"struct %s* inc_%s_ptree(struct %s* ptree)" "\n"
			"{" "\n"
				"\t" "if (ptree) ptree->refcount++;" "\n"
				"\t" "return ptree;" "\n"
			"}" "\n"
			"\n"
		"", type, type, type);
	}
	
	EXIT;
}
