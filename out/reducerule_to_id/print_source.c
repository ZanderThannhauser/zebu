
#include <debug.h>

#include <yacc/structinfo/struct.h>

#include <yacc/reductioninfo/print_source.h>

#include "../string_to_id/string_to_id.h"

#include "struct.h"
#include "print_source.h"

void reducerule_to_id_print_source(
	struct reducerule_to_id* this,
	struct string_to_id* stoi,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"switch (r)" "\n"
		"{" "\n"
	"");
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct reducerule_to_id_node* const ele = node->item;
		
		fprintf(stream, ""
			"\t" "case %u:" "\n"
			"\t" "{" "\n"
		"", ele->id);
		
		fprintf(stream, ""
			"\t" "\t" "struct %s* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));" "\n"
		"", ele->structinfo->name->chars);
		
		reductioninfo_print_source(ele->reductioninfo, stream);
		
		fprintf(stream, ""
			"\t" "\t" "d = value, g = %u;" "\n"
			"\t" "\t" "break;" "\n"
			"\t" "}" "\n"
		"", string_to_id(stoi, ele->reduce_as));
	}
	
	fprintf(stream, ""
		"}"
	"");
	
	EXIT;
}

















