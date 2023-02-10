
#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <yacc/structinfo/struct.h>

#include <yacc/reductioninfo/print_source.h>

#include "../string_to_id/string_to_id.h"

#include "struct.h"
#include "print_source.h"

void reducerule_to_id_print_source(
	struct reducerule_to_id* this,
	struct string_to_id* stoi,
	const char* prefix,
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
			"case %u:" "\n"
			"{" "\n"
		"", ele->id);
		
		fprintf(stream, ""
			"struct %s_%s* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));" "\n"
			"value->refcount = 1;" "\n"
			"#if ZEBU_LINE_NUMBERS" "\n"
			"value->startline = -1;" "\n"
			"value->endline = 0;" "\n"
			"#endif" "\n"
		"", prefix, ele->grammar->chars);
		
		reductioninfo_print_source(ele->reductioninfo, ele->structinfo, ele->grammar->chars, prefix, stream);
		
		fprintf(stream, ""
			"d = value, g = %u;" "\n"
			"break;" "\n"
			"}" "\n"
		"", string_to_id(stoi, ele->reduce_as));
	}
	
	fprintf(stream, ""
		"}"
	"");
	
	EXIT;
}



























