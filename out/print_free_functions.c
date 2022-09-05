
#include <debug.h>

#include <yacc/structinfo/struct.h>

#include "print_free_functions.h"

void print_free_functions(
	struct avl_tree_t* structinfos,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"void free_token(struct token* this)" "\n"
		"{" "\n"
			"\t" "if (this)" "\n"
			"\t" "{" "\n"
				"\t" "\t" "free(this->data);" "\n"
				"\t" "\t" "free(this);" "\n"
			"\t" "}" "\n"
		"}" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"void free_%s_tree(struct %s* ptree);" "\n"
			"" "\n"
		"", ele->name->chars, ele->name->chars);
	}
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"void free_%s_tree(struct %s* ptree)" "\n"
			"{" "\n"
			"\t" "if (ptree)" "\n"
			"\t" "{" "\n"
		"", ele->name->chars, ele->name->chars);
		
		for (struct avl_node_t* node = ele->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			
			switch (ele->kind)
			{
				case sin_token:
					fprintf(stream, ""
						"\t" "\t" "free_token(ptree->%s);" "\n"
					"", field);
					break;
				
				case sin_grammar:
					fprintf(stream, ""
						"\t" "\t" "free_%s_tree(ptree->%s);" "\n"
					"", ele->grammar.name->chars, field);
					break;
				
				default:
					TODO;
					break;
			}
		}
		
		fprintf(stream, ""
				"\t" "\t" "free(ptree);" "\n"
				"\t" "}" "\n"
			"}" "\n"
			"" "\n"
		"");
	}
	
	EXIT;
}

