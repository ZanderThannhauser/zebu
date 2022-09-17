
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <yacc/structinfo/struct.h>

#include "print_free_functions.h"

void print_free_function_prototypes(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"extern void free_token(struct token* this);" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"extern void free_%s_%s_ptree(struct %s_%s* ptree);" "\n"
			"" "\n"
		"", prefix, ele->name->chars, prefix, ele->name->chars);
	}
	
	EXIT;
}

void print_free_functions(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"void free_token(struct token* this)" "\n"
		"{" "\n"
		"\t" "if (this && !--this->refcount)" "\n"
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
			"void free_%s_%s_ptree(struct %s_%s* ptree);" "\n"
			"" "\n"
		"", prefix, ele->name->chars, prefix, ele->name->chars);
	}
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"void free_%s_%s_ptree(struct %s_%s* ptree)" "\n"
			"{" "\n"
			"\t" "if (ptree && !--ptree->refcount)" "\n"
			"\t" "{" "\n"
		"", prefix, ele->name->chars, prefix, ele->name->chars);
		
		for (struct avl_node_t* node = ele->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			
			switch (ele->kind)
			{
				case sin_token_scalar:
					fprintf(stream, ""
						"\t" "\t" "free_token(ptree->%s);" "\n"
					"", field);
					break;
				
				case sin_token_array:
				{
					fprintf(stream, ""
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "\t" "free_token(ptree->%s.data[i]);" "\n"
						"\t" "\t" "free(ptree->%s.data);" "\n"
					"", field, field, field);
					break;
				}
				
				case sin_grammar_scalar:
					fprintf(stream, ""
						"\t" "\t" "free_%s_%s_ptree(ptree->%s);" "\n"
					"", prefix, ele->grammar->chars, field);
					break;
				
				case sin_grammar_array:
				{
					fprintf(stream, ""
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "\t" "free_%s_%s_ptree(ptree->%s.data[i]);" "\n"
						"\t" "\t" "free(ptree->%s.data);" "\n"
					"", field, prefix, ele->grammar->chars, field, field);
					break;
				}
				
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





