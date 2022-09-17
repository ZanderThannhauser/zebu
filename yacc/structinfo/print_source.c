
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include "struct.h"
#include "print_source.h"

void structinfo_print_source(
	struct structinfo* this,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct %s_%s" "\n"
		"{" "\n"
	"", prefix, this->name->chars);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		
		switch (ele->kind)
		{
			case sin_token_scalar:
				fprintf(stream, ""
					"\t" "struct token* %s;" "\n"
				"", ele->name->chars);
				break;
			
			case sin_token_array:
				fprintf(stream, ""
					"\t" "struct {" "\n"
					"\t" "\t" "struct token** data;" "\n"
					"\t" "\t" "unsigned n, cap;" "\n"
					"\t" "} %s;" "\n"
				"", ele->name->chars);
				break;
			
			case sin_grammar_scalar:
				fprintf(stream, ""
					"\t" "struct %s_%s* %s;" "\n"
				"", prefix, ele->grammar->chars, ele->name->chars);
				break;
			
			case sin_grammar_array:
				fprintf(stream, ""
					"\t" "struct {" "\n"
					"\t" "\t" "struct %s_%s** data;" "\n"
					"\t" "\t" "unsigned n, cap;" "\n"
					"\t" "} %s;" "\n"
				"", prefix, ele->grammar->chars, ele->name->chars);
				break;
			
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

























