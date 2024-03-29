
#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <named/structinfo/struct.h>

#include "print_inc_functions.h"

void print_inc_function_prototypes(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"extern struct %s_token* inc_%s_token(struct %s_token* token);" "\n"
	"", prefix, prefix, prefix);
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct named_structinfo* const ele = node->item;
		
		const char* type = ele->name->chars;
		
		fprintf(stream, ""
			"extern struct %s_%s* inc_%s_%s(struct %s_%s* ptree);" "\n"
		"", prefix, type, prefix, type, prefix, type);
	}
	
	EXIT;
}

void print_inc_functions(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct %s_token* inc_%s_token(struct %s_token* token)" "\n"
		"{" "\n"
			"\t" "if (token) token->refcount++;" "\n"
			"\t" "return token;" "\n"
		"}" "\n"
	"", prefix, prefix, prefix);
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct named_structinfo* const ele = node->item;
		
		const char* type = ele->name->chars;
		
		fprintf(stream, ""
			"struct %s_%s* inc_%s_%s(struct %s_%s* ptree)" "\n"
			"{" "\n"
				"\t" "if (ptree) ptree->refcount++;" "\n"
				"\t" "return ptree;" "\n"
			"}" "\n"
			"\n"
		"", prefix, type, prefix, type, prefix, type);
	}
	
	EXIT;
}















