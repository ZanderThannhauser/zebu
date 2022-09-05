
#include <debug.h>

#include <set/string/foreach.h>
#include <set/string/is_empty.h>

#include <yacc/structinfo/struct.h>

#include "struct.h"
#include "print_source.h"

void reductioninfo_print_source(
	struct reductioninfo* this,
	struct structinfo* structinfo,
	FILE* stream)
{
	ENTER;
	
	assert(this);
	
	if (this->grammar && this->grammar->chars[0] == '(')
	{
		fprintf(stream, ""
			"\t" "\t" "{" "\n"
			"\t" "\t" "\t" "struct %s* trie = data.data[--yacc.n, --data.n];" "\n"
		"", structinfo->name->chars);
		
		for (struct avl_node_t* node = structinfo->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			
			if (ele->kind == sin_grammar)
			{
				fprintf(stream, ""
					"\t" "\t" "\t" "if (trie->%s) { free_%s_tree(value->%s); value->%s = trie->%s; }" "\n"
				"", field, ele->grammar.name->chars, field, field, field);
			}
			else
			{
				fprintf(stream, ""
					"\t" "\t" "\t" "if (trie->%s) { free_token(value->%s); value->%s = trie->%s; }" "\n"
				"", field, field, field, field);
			}
		}
		
		fprintf(stream, ""
			"\t" "\t" "\t" "free(trie);" "\n"
			"\t" "\t" "};" "\n"
		"");
		
	}
	else
	{
		bool once = true;
		
		char* type = NULL;
		
		if (this->grammar && asprintf(&type, "%s_tree", this->grammar->chars) < 0)
			abort();
		
		stringset_foreach(this->tags, ({
			void runme(struct string* tag)
			{
				if (once)
				{
					fprintf(stream, ""
						"\t" "\t" "free_%s(value->%s), value->%s = data.data[--yacc.n, --data.n];" "\n"
					"", type ?: "token", tag->chars, tag->chars);
					once = false;
				}
				else
				{
					fprintf(stream, ""
						"\t" "\t" "free_%s(value->%s), value->%s = inc_%s(data.data[data.n]);" "\n"
					"", type ?: "token", tag->chars, tag->chars, type);
				}
			}
			runme;
		}));
		
		if (stringset_is_empty(this->tags))
		{
			fprintf(stream, ""
				"\t" "\t" "free_%s(data.data[--yacc.n, --data.n]);" "\n"
			"", type ?: "token");
		}
		
		free(type);
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(this->prev, structinfo, stream);
	}
	
	EXIT;
}




















