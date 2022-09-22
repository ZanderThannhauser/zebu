
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include "node.h"
#include "struct.h"
#include "print_source.h"

void structinfo_print_source(
	struct structinfo* this,
	struct string* name,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct %s_%s" "\n"
		"{" "\n"
	"", prefix, name->chars);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		
		const char* const name = ele->name->chars;
		
		switch (ele->type)
		{
			case snt_token_scalar:
				fprintf(stream, ""
					"\t" "struct token* %s;" "\n"
				"", name);
				break;
			
			case snt_token_array:
				fprintf(stream, ""
					"\t" "struct {" "\n"
					"\t" "\t" "struct token** data;" "\n"
					"\t" "\t" "unsigned n, cap;" "\n"
					"\t" "} %s;" "\n"
				"", name);
				break;
			
			case snt_grammar_scalar:
			{
				const char* grammar = ele->grammar.name->chars;
				
				fprintf(stream, ""
					"\t" "struct %s_%s* %s;" "\n"
				"", prefix, grammar, name);
				break;
			}
			
			case snt_grammar_array:
			{
				const char* grammar = ele->grammar.name->chars;
				
				fprintf(stream, ""
					"\t" "struct {" "\n"
					"\t" "\t" "struct %s_%s** data;" "\n"
					"\t" "\t" "unsigned n, cap;" "\n"
					"\t" "} %s;" "\n"
				"", prefix, grammar, name);
				break;
			}
			
			case snt_user_defined:
			{
				struct string* const type = ele->user_defined.type;
				
				fprintf(stream, ""
					"\t" "%.*s %s;" "\n"
				"", type->len, type->chars, name);
				break;
			}
			
			default:
				TODO;
				break;
		}
	}
	
	fprintf(stream, ""
		"\t" "unsigned refcount;" "\n"
		"};" "\n"
		"" "\n"
	"");
	
	EXIT;
}

























