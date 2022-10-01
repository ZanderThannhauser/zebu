
#include <assert.h>
#include <string.h>

#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <named/structinfo/struct.h>

#include <misc/format_flags/struct.h>

#include <yacc/structinfo/node.h>
#include <yacc/structinfo/struct.h>

#include "print_tree_functions.h"

void print_tree_function_prototypes(
	struct avl_tree_t* structinfos,
	const char* output_prefix,
	FILE* stream)
{
	ENTER;
	
	TODO;
	#if 0
	fprintf(stream, ""
		"extern void print_token_leaf(struct link* links, enum prefix p, const char* name, struct token* token);" "\n"
		"extern void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name);" "\n"
	"");
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct structinfo* const ele = node->item;
		
		fprintf(stream, ""
			"extern void print_%s_%s(struct link* links, enum prefix p, const char* name, struct %s* ptree);" "\n"
			"\n"
		"", output_prefix, name->chars, name->chars);
	}
	#endif
	
	EXIT;
}

void print_tree_functions(
	struct avl_tree_t* structinfos,
	const char* output_prefix,
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
		"void print_token_leaf(struct link* links, enum prefix p, const char* name, struct %s_token* token)" "\n"
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
		"void print_scanf_leaf(struct link* links, enum prefix p, const char* name, const char* format, ...)" "\n"
		"{" "\n"
			"\t" "va_list ap;" "\n"
			"\t" "print_links(links);" "\n"
			"\t" "switch (p)" "\n"
			"\t" "{" "\n"
				"\t" "\t" "case p_root: break;" "\n"
				"\t" "\t" "case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
				"\t" "\t" "case p_last_child: fputs(\"└── \", stdout); break;" "\n"
			"\t" "}" "\n"
			"\t" "printf(\"\\e[32m%%s\\e[0m (\\e[35m%%s\\e[m: \\e[35m\", name, format);" "\n"
			"\t" "va_start(ap, format);" "\n"
			"\t" "vprintf(format, ap);" "\n"
			"\t" "va_end(ap);" "\n"
			"\t" "printf(\"\\e[0m)\\n\");" "\n"
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
	"", output_prefix);
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct named_structinfo* const ele = node->item;
		
		char* const name = ele->name->chars;
		
		fprintf(stream, ""
			"void print_%s_%s(struct link* links, enum prefix p, const char* name, struct %s_%s* ptree);" "\n"
			"\n"
		"", output_prefix, name, output_prefix, name);
	};
	
	for (struct avl_node_t* node = structinfos->head; node; node = node->next)
	{
		struct named_structinfo* const ele = node->item;
		
		char* const name = ele->name->chars;
		
		struct structinfo* const structinfo = ele->structinfo;
		
		fprintf(stream, ""
			"void print_%s_%s(struct link* links, enum prefix p, const char* name, struct %s_%s* ptree)" "\n"
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
		"", output_prefix, name, output_prefix, name, name);
		
		for (struct avl_node_t* node = structinfo->tree->head; node; node = node->next)
		{
			struct structinfo_node* const ele = node->item;
			
			const char* field = ele->name->chars;
			
			const char* prefix = node->next ? "p_not_last_child" : "p_last_child";
			
			switch (ele->type)
			{
				case snt_token_scalar:
				{
					fprintf(stream, ""
						"\t" "if (ptree->%s)" "\n"
						"\t" "\t" "print_token_leaf(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"\t" "else" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"token\", \"%s\");" "\n"
					"", field, prefix, field, field, prefix, field);
					break;
				}
				
				case snt_token_array:
				{
					fprintf(stream, ""
						"\t" "if (ptree->%s.n)" "\n"
						"\t" "{" "\n"
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "{" "\n"
						"\t" "\t" "\t" "char label[%zu + 30];" "\n"
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
				
				case snt_grammar_scalar:
				{
					const char* grammar_chars = ele->grammar.name->chars;
					
					fprintf(stream, ""
						"\t" "if (ptree->%s)" "\n"
						"\t" "\t" "print_%s_%s(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"\t" "else" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"%s\", \"%s\");" "\n"
					"", field,
					output_prefix, grammar_chars, prefix, field, field,
					prefix, grammar_chars, field);
					break;
				}
				
				case snt_grammar_array:
				{
					const char* grammar_chars = ele->grammar.name->chars;
					
					fprintf(stream, ""
						"\t" "if (ptree->%s.n)" "\n"
						"\t" "{" "\n"
						"\t" "\t" "for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
						"\t" "\t" "{" "\n"
						"\t" "\t" "\t" "char label[%zu + 30];" "\n"
						"\t" "\t" "\t" "snprintf(label, sizeof(label), \"%s[%%u]\", i);" "\n"
						"\t" "\t" "\t" "print_%s_%s(new ?: links, i + 1 < n ? p_not_last_child : %s, label, ptree->%s.data[i]);" "\n"
						"\t" "\t" "}" "\n"
						"\t" "}" "\n"
						"\t" "else" "\n"
						"\t" "{" "\n"
						"\t" "\t" "print_empty_leaf(new ?: links, %s, \"%s[]\", \"%s\");" "\n"
						"\t" "}" "\n"
					"", field,
					field,
					strlen(field),
					field,
					output_prefix, grammar_chars,
					prefix, field,
					prefix, grammar_chars, field);
					break;
				}
				
				case snt_scanf_scalar:
				{
					struct format_flags* fflags = ele->scanf.fflags;
					
					fprintf(stream, ""
						"\t" "print_scanf_leaf(new ?: links, %s, \"%s\", \"%%%s%c\", ptree->%s);" "\n"
					"", prefix, field, fflags->length_modifier_text, fflags->conversion, field);
					
					break;
				}
				
				case snt_scanf_array:
					TODO;
					break;
				
				case snt_user_defined:
				{
					struct string *const type = ele->user_defined.type;
					
					fprintf(stream, ""
						"\t" "print_empty_leaf(new ?: links, %s, \"%.*s\", \"%s\");" "\n"
					"", prefix, type->len, type->chars, field);
					
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
















