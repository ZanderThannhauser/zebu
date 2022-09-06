
#include <debug.h>

#include <set/string/add.h>

#include "struct.h"
#include "print_source.h"

void structinfo_print_source(
	struct structinfo* this,
	struct stringset* done,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"struct %s" "\n"
		"{" "\n"
	"", this->name->chars);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		
		switch (ele->kind)
		{
			case sin_token:
			{
				fprintf(stream, ""
					"\t" "struct token* %s;" "\n"
				"", ele->name->chars);
				break;
			}
			
			case sin_grammar:
			{
				fprintf(stream, ""
					"\t" "struct %s* %s;" "\n"
				"", ele->grammar.name->chars, ele->name->chars);
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
	
	stringset_add(done, this->name);
	
	EXIT;
}

























