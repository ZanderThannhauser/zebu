
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
	
	switch (this->kind)
	{
		case rik_token:
		{
			bool once = true;
			
			stringset_foreach(this->tags, ({
				void runme(struct string* tag)
				{
					if (once)
					{
						fprintf(stream, ""
							"\t" "\t" "free_token(value->%s), value->%s = data.data[--yacc.n, --data.n];" "\n"
						"", tag->chars, tag->chars);
						once = false;
					}
					else
					{
						fprintf(stream, ""
							"\t" "\t" "free_token(value->%s), value->%s = inc_token(data.data[data.n]);" "\n"
						"", tag->chars, tag->chars);
					}
				}
				runme;
			}));
			
			if (stringset_is_empty(this->tags))
			{
				fprintf(stream, ""
					"\t" "\t" "free_token(data.data[--yacc.n, --data.n]);" "\n"
				"");
			}
			break;
		}
		
		case rik_grammar:
		{
			bool once = true;
			
			const char* type = this->grammar->chars;
			
			stringset_foreach(this->tags, ({
				void runme(struct string* tag)
				{
					if (once)
					{
						fprintf(stream, ""
							"\t" "\t" "free_%s_tree(value->%s), value->%s = data.data[--yacc.n, --data.n];" "\n"
						"", type, tag->chars, tag->chars);
						once = false;
					}
					else
					{
						fprintf(stream, ""
							"\t" "\t" "free_%s_tree(value->%s), value->%s = inc_%s_tree(data.data[data.n]);" "\n"
						"", type, tag->chars, tag->chars, type);
					}
				}
				runme;
			}));
			
			if (stringset_is_empty(this->tags))
			{
				fprintf(stream, ""
					"\t" "\t" "free_%s_tree(data.data[--yacc.n, --data.n]);" "\n"
				"", type);
			}
			
			break;
		}
		
		case rik_trie:
		{
			fprintf(stream, ""
				"\t" "\t" "{" "\n"
				"\t" "\t" "\t" "struct %s* trie = data.data[--yacc.n, --data.n];" "\n"
			"", structinfo->name->chars);
			
			for (struct avl_node_t* node = structinfo->tree->head; node; node = node->next)
			{
				struct structinfo_node* const ele = node->item;
				
				const char* field = ele->name->chars;
				
				switch (ele->kind)
				{
					case sin_token:
						fprintf(stream, ""
							"\t" "\t" "\t" "if (trie->%s) { free_token(value->%s); value->%s = trie->%s; }" "\n"
						"", field, field, field, field);
						break;
					
					case sin_grammar:
						fprintf(stream, ""
							"\t" "\t" "\t" "if (trie->%s) { free_%s_tree(value->%s); value->%s = trie->%s; }" "\n"
						"", field, ele->grammar.name->chars, field, field, field);
						break;
					
					default:
						TODO;
						break;
				}
			}
			
			fprintf(stream, ""
				"\t" "\t" "\t" "free(trie);" "\n"
				"\t" "\t" "};" "\n"
			"");
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(this->prev, structinfo, stream);
	}
	
	EXIT;
}




















