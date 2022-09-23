
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <named/structinfo/struct.h>

#include <yacc/structinfo/node.h>
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
		struct named_structinfo* const ele = node->item;
		
		char* const name = ele->name->chars;
		
		fprintf(stream, ""
			"extern void free_%s_%s(struct %s_%s* ptree);" "\n"
			"" "\n"
		"", prefix, name, prefix, name);
	}
	
	EXIT;
}

void print_free_functions(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	print_free_function_prototypes(structinfos, prefix, stream);
	
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
		struct named_structinfo* const ele = node->item;
		
		char* const name = ele->name->chars;
		
		fprintf(stream, ""
			"void free_%s_%s(struct %s_%s* ptree)" "\n"
			"{" "\n"
			"\t" "if (ptree && !--ptree->refcount)" "\n"
			"\t" "{" "\n"
		"", prefix, name, prefix, name);
		
		for (struct avl_node_t* node = ele->structinfo->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			
			switch (ele->type)
			{
				case snt_token_scalar:
				{
					fprintf(stream, ""
						"\t" "\t" "free_token(ptree->%s);" "\n"
					"", field);
					break;
				}
				
				case snt_token_array:
				{
					fprintf(stream, ""
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "\t" "free_token(ptree->%s.data[i]);" "\n"
						"\t" "\t" "free(ptree->%s.data);" "\n"
					"", field, field, field);
					break;
				}
				
				case snt_grammar_scalar:
				{
					fprintf(stream, ""
						"\t" "\t" "free_%s_%s(ptree->%s);" "\n"
					"", prefix, ele->grammar.name->chars, field);
					break;
				}
				
				case snt_grammar_array:
				{
					fprintf(stream, ""
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "\t" "free_%s_%s(ptree->%s.data[i]);" "\n"
						"\t" "\t" "free(ptree->%s.data);" "\n"
					"", field, prefix, ele->grammar.name->chars, field, field);
					break;
				}
				
				case snt_user_defined:
				{
					struct string* const type = ele->user_defined.type;
					const char* const destructor = ele->user_defined.destructor->chars;
					
					fprintf(stream, ""
						"\t" "\t" "void %s(%.*s);" "\n"
						"\t" "\t" "%s(ptree->%s);" "\n"
					"", destructor, type->len, type->chars, destructor, field);
					
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





