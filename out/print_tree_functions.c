
#include <assert.h>
#include <string.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <yacc/structinfo/struct.h>

#include "print_tree_functions.h"

void print_tree_function_prototypes(
	struct avl_tree_t* structinfos,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"extern void print_token_leaf(struct link* links, enum prefix p, const char* name, struct token* token);" "\n"
		"extern void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name);" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"extern void print_%s_ptree(struct link* links, enum prefix p, const char* name, struct %s* ptree);" "\n"
			"\n"
		"", ele->name->chars, ele->name->chars);
	}
	
	EXIT;
}

void print_tree_functions(
	struct avl_tree_t* structinfos,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, ""
		"#include <stdbool.h>" "\n"
		"\n"
		"struct link" "\n"
		"{" "\n"
			"\t" "bool is_last;" "\n"
			"\t" "struct link* prev;" "\n"
		"};" "\n"
		"\n"
		"static void print_links(struct link* link)" "\n"
		"{" "\n"
			"\t" "if (!link) return;" "\n"
			"\t" "\n"
			"\t" "print_links(link->prev);" "\n"
			"\t" "\n"
			"\t" "if (link->is_last)" "\n"
				"\t" "\t" "fputs(\"    \", stdout);" "\n"
			"\t" "else" "\n"
				"\t" "\t" "fputs(\"│   \", stdout);" "\n"
		"}" "\n"
		"\n"
		"static void print_tree_escape(char *out, char in)" "\n"
		"{" "\n"
		"\tswitch (in)" "\n"
		"\t{" "\n"
		"\t\tcase \' \':" "\n"
		"\t\tcase \'~\':" "\n"
		"\t\tcase \'!\':" "\n"
		"\t\tcase \'@\':" "\n"
		"\t\tcase \'#\':" "\n"
		"\t\tcase \'$\':" "\n"
		"\t\tcase \'%%\':" "\n"
		"\t\tcase \'^\':" "\n"
		"\t\tcase \'&\':" "\n"
		"\t\tcase \'*\':" "\n"
		"\t\tcase \'-\':" "\n"
		"\t\tcase \'+\':" "\n"
		"\t\tcase \'=\':" "\n"
		"\t\tcase \'|\':" "\n"
		"\t\tcase \'<\': case \'>\':" "\n"
		"\t\tcase \'(\': case \')\':" "\n"
		"\t\tcase \'{\': case \'}\':" "\n"
		"\t\tcase \'[\': case \']\':" "\n"
		"\t\tcase \':\': case \';\':" "\n"
		"\t\tcase \',\': case \'.\':" "\n"
		"\t\tcase \'_\':" "\n"
		"\t\tcase \'`\':" "\n"
		"\t\tcase \'0\' ... \'9\':" "\n"
		"\t\tcase \'a\' ... \'z\':" "\n"
		"\t\tcase \'A\' ... \'Z\':" "\n"
		"\t\t\t*out++ = in;" "\n"
		"\t\t\t*out = 0;" "\n"
		"\t\t\tbreak;" "\n"
		"\t\t" "\n"
		"\t\tcase \'\\\\\': *out++ = \'\\\\\', *out++ = \'\\\\\', *out = 0; break;" "\n"
		"\t\t" "\n"
		"\t\tcase \'\\\'\': *out++ = \'\\\\\', *out++ = \'\\\'\', *out = 0; break;" "\n"
		"\t\t" "\n"
		"\t\tcase \'\\\"\': *out++ = \'\\\\\', *out++ = \'\\\"\', *out = 0; break;" "\n"
		"\t\t" "\n"
		"\t\tcase \'\\t\': *out++ = \'\\\\\', *out++ = \'t\', *out = 0; break;" "\n"
		"\t\t" "\n"
		"\t\tcase \'\\n\': *out++ = \'\\\\\', *out++ = \'n\', *out = 0; break;" "\n"
		"\t\t" "\n"
		"\t\tdefault:" "\n"
		"\t\t\tsprintf(out, \"\\\\x%%02X\", in);" "\n"
		"\t\t\tbreak;" "\n"
		"\t}" "\n"
		"}" "\n"
		"\n"
		"enum prefix" "\n"
		"{" "\n"
			"\t" "p_root," "\n"
			"\t" "p_not_last_child," "\n"
			"\t" "p_last_child," "\n"
		"};" "\n"
		"\n"
		"void print_token_leaf(struct link* links, enum prefix p, const char* name, struct token* token)" "\n"
		"{" "\n"
			"\t" "print_links(links);" "\n"
			"\t" "switch (p)" "\n"
			"\t" "{" "\n"
				"\t" "\t" "case p_root: break;" "\n"
				"\t" "\t" "case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
				"\t" "\t" "case p_last_child: fputs(\"└── \", stdout); break;" "\n"
			"\t" "}" "\n"
			"\t" "printf(\"\\e[32m%%s\\e[0m (\\e[35m\\\"\", name);" "\n"
			"\t" "char escape[10];" "\n"
			"\t" "for (unsigned i = 0, n = token->len; i < n; i++)" "\n"
			"\t" "\t" "print_tree_escape(escape, token->data[i]), fputs(escape, stdout);" "\n"
			"\t" "printf(\"\\\"\\e[0m)\\n\");" "\n"
		"}" "\n"
		"\n"
		"void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name)" "\n"
		"{" "\n"
			"\t" "print_links(links);" "\n"
			"\t" "switch (p)" "\n"
			"\t" "{" "\n"
				"\t" "\t" "case p_root: break;" "\n"
				"\t" "\t" "case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
				"\t" "\t" "case p_last_child: fputs(\"└── \", stdout); break;" "\n"
			"\t" "}" "\n"
			"\t" "printf(\"\\e[31m%%s\\e[0m (\\e[36m%%s\\e[0m)\\n\", name, type);" "\n"
		"}" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"void print_%s_ptree(struct link* links, enum prefix p, const char* name, struct %s* ptree);" "\n"
			"\n"
		"", ele->name->chars, ele->name->chars);
	};
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"void print_%s_ptree(struct link* links, enum prefix p, const char* name, struct %s* ptree)" "\n"
			"{" "\n"
				"\t" "print_links(links);" "\n"
				"\t" "\n"
				"\t" "struct link* new = NULL;" "\n"
				"\t" "\n"
				"\t" "switch (p)" "\n"
				"\t" "{" "\n"
				"\t" "\t" "case p_root:" "\n"
				"\t" "\t" "\t" "break;" "\n"
				"\t" "\t" "\n"
				"\t" "\t" "case p_not_last_child:" "\n"
				"\t" "\t" "\t" "fputs(\"├── \", stdout);" "\n"
				"\t" "\t" "\t" "new = malloc(sizeof(*new));" "\n"
				"\t" "\t" "\t" "new->is_last = false;" "\n"
				"\t" "\t" "\t" "new->prev = links;" "\n"
				"\t" "\t" "\t" "break;" "\n"
				"\t" "\t" "\n"
				"\t" "\t" "case p_last_child:" "\n"
				"\t" "\t" "\t" "fputs(\"└── \", stdout);" "\n"
				"\t" "\t" "\t" "new = malloc(sizeof(*new));" "\n"
				"\t" "\t" "\t" "new->is_last = true;" "\n"
				"\t" "\t" "\t" "new->prev = links;" "\n"
				"\t" "\t" "break;" "\n"
				"\t" "}" "\n"
				"\t" "printf(\"\\e[34m%%s\\e[m (\\e[36m%s\\e[m)\\n\", name);" "\n"
		"", ele->name->chars, ele->name->chars, ele->name->chars);
		
		for (struct avl_node_t* node = ele->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			const char* prefix = node->next ? "p_not_last_child" : "p_last_child";
			
			switch (ele->kind)
			{
				case sin_token_scalar:
				{
					fprintf(stream, ""
						"\t" "if (ptree->%s)" "\n"
						"\t" "\t" "print_token_leaf(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"\t" "else" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"token\", \"%s\");" "\n"
					"", field, prefix, field, field, prefix, field);
					break;
				}
				
				case sin_token_array:
				{
					fprintf(stream, ""
						"\t" "if (ptree->%s.n)" "\n"
						"\t" "{" "\n"
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "{" "\n"
						"\t" "\t" "\t" "char label[%lu + 30];" "\n"
						"\t" "\t" "\t" "snprintf(label, sizeof(label), \"%s[%%u]\", i);" "\n"
						"\t" "\t" "\t" "print_token_leaf(new ?: links, i + 1 < n ? p_not_last_child : %s, label, ptree->%s.data[i]);" "\n"
						"\t" "\t" "}" "\n"
						"\t" "}" "\n"
						"\t" "else" "\n"
						"\t" "{" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"token[]\", \"%s\");" "\n"
						"\t" "}" "\n"
					"", field,
					field,
					strlen(field),
					field,
					prefix, field,
					prefix, field);
					
					break;
				}
				
				case sin_grammar_scalar:
				{
					const char* grammar_chars = ele->grammar->chars;
					
					fprintf(stream, ""
						"\t" "if (ptree->%s)" "\n"
						"\t" "\t" "print_%s_ptree(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"\t" "else" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"%s\", \"%s\");" "\n"
					"", field, grammar_chars, prefix, field, field, prefix, grammar_chars, field);
					break;
				}
				
				case sin_grammar_array:
				{
					const char* grammar_chars = ele->grammar->chars;
					
					fprintf(stream, ""
						"\t" "if (ptree->%s.n)" "\n"
						"\t" "{" "\n"
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "{" "\n"
						"\t" "\t" "\t" "char label[%lu + 30];" "\n"
						"\t" "\t" "\t" "snprintf(label, sizeof(label), \"%s[%%u]\", i);" "\n"
						"\t" "\t" "\t" "print_%s_ptree(new ?: links, i + 1 < n ? p_not_last_child : %s, label, ptree->%s.data[i]);" "\n"
						"\t" "\t" "}" "\n"
						"\t" "}" "\n"
						"\t" "else" "\n"
						"\t" "{" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"%s[]\", \"%s\");" "\n"
						"\t" "}" "\n"
					"", field, field, strlen(field), field, grammar_chars, prefix, field, prefix, grammar_chars, field);
					
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		
		fprintf(stream, ""
			"\t" "free(new);" "\n"
			"}" "\n"
		"");
	}
	
	EXIT;
}
















