
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
		"    bool is_last;" "\n"
		"    struct link* prev;" "\n"
		"};" "\n"
		"\n"
		"static void print_links(struct link* link)" "\n"
		"{" "\n"
		"    if (!link) return;" "\n"
		"    print_links(link->prev);" "\n"
		"    fputs(link->is_last ? \"    \" : \"│   \", stdout);" "\n"
		"}" "\n"
		"\n"
		"static void print_tree_escape(char *out, char in)" "\n"
		"{" "\n"
		"    switch (in)" "\n"
		"    {" "\n"
		"        case \' \':" "\n"
		"        case \'~\':" "\n"
		"        case \'!\':" "\n"
		"        case \'@\':" "\n"
		"        case \'#\':" "\n"
		"        case \'$\':" "\n"
		"        case \'%%\':" "\n"
		"        case \'^\':" "\n"
		"        case \'&\':" "\n"
		"        case \'*\':" "\n"
		"        case \'-\':" "\n"
		"        case \'+\':" "\n"
		"        case \'=\':" "\n"
		"        case \'|\':" "\n"
		"        case \'<\': case \'>\':" "\n"
		"        case \'(\': case \')\':" "\n"
		"        case \'{\': case \'}\':" "\n"
		"        case \'[\': case \']\':" "\n"
		"        case \':\': case \';\':" "\n"
		"        case \',\': case \'.\':" "\n"
		"        case \'_\':" "\n"
		"        case \'/\':" "\n"
		"        case \'`\':" "\n"
		"        case \'0\' ... \'9\':" "\n"
		"        case \'a\' ... \'z\':" "\n"
		"        case \'A\' ... \'Z\':" "\n"
		"            *out++ = in;" "\n"
		"            *out = 0;" "\n"
		"            break;" "\n"
		"        " "\n"
		"        case \'\\\\\': *out++ = \'\\\\\', *out++ = \'\\\\\', *out = 0; break;" "\n"
		"        " "\n"
		"        case \'\\\'\': *out++ = \'\\\\\', *out++ = \'\\\'\', *out = 0; break;" "\n"
		"        " "\n"
		"        case \'\\\"\': *out++ = \'\\\\\', *out++ = \'\\\"\', *out = 0; break;" "\n"
		"        " "\n"
		"        case \'\\t\': *out++ = \'\\\\\', *out++ = \'t\', *out = 0; break;" "\n"
		"        " "\n"
		"        case \'\\n\': *out++ = \'\\\\\', *out++ = \'n\', *out = 0; break;" "\n"
		"        " "\n"
		"        default:" "\n"
		"            sprintf(out, \"\\\\x%%02X\", in);" "\n"
		"            break;" "\n"
		"    }" "\n"
		"}" "\n"
		"\n"
		"enum prefix" "\n"
		"{" "\n"
			"p_root," "\n"
			"p_not_last_child," "\n"
			"p_last_child," "\n"
		"};" "\n"
		"\n"
		"void print_token_leaf(struct link* links, enum prefix p, const char* name, struct %s_token* token)" "\n"
		"{" "\n"
			"print_links(links);" "\n"
				"switch (p)" "\n"
				"{" "\n"
					"case p_root: break;" "\n"
					"case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
					"case p_last_child: fputs(\"└── \", stdout); break;" "\n"
				"}" "\n"
				"printf(\"\\e[32m%%s\\e[0m (\\e[35m\\\"\", name);" "\n"
				"char escape[10];" "\n"
				"for (unsigned i = 0, n = token->len; i < n; i++)" "\n"
					"print_tree_escape(escape, token->data[i]), fputs(escape, stdout);" "\n"
				"printf(\"\\\"\\e[0m)\");" "\n"
				"#if ZEBU_LINE_NUMBERS" "\n"
				"printf(\" on line %%u\", token->line);" "\n"
				"#endif" "\n"
				"printf(\"\\n\");" "\n"
		"}" "\n"
		"\n"
		"void print_scanf_leaf(struct link* links, enum prefix p, const char* name, const char* format, ...)" "\n"
		"{" "\n"
			"va_list ap;" "\n"
			"print_links(links);" "\n"
			"switch (p)" "\n"
			"{" "\n"
				"case p_root: break;" "\n"
				"case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
				"case p_last_child: fputs(\"└── \", stdout); break;" "\n"
			"}" "\n"
			"printf(\"\\e[32m%%s\\e[0m (\\e[35m%%s\\e[m: \\e[35m\", name, format);" "\n"
			"va_start(ap, format);" "\n"
			"vprintf(format, ap);" "\n"
			"va_end(ap);" "\n"
			"printf(\"\\e[0m)\\n\");" "\n"
		"}" "\n"
		"\n"
		"void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name)" "\n"
		"{" "\n"
			"print_links(links);" "\n"
			"switch (p)" "\n"
			"{" "\n"
				"case p_root: break;" "\n"
				"case p_not_last_child: fputs(\"├── \", stdout); break;" "\n"
				"case p_last_child: fputs(\"└── \", stdout); break;" "\n"
			"}" "\n"
			"printf(\"\\e[31m%%s\\e[0m (\\e[36m%%s\\e[0m)\\n\", name, type);" "\n"
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
				"print_links(links);" "\n"
				"\n"
				"struct link* new = NULL;" "\n"
				"\n"
				"switch (p)" "\n"
				"{" "\n"
					"case p_root:" "\n"
						"break;" "\n"
					"\n"
					"case p_not_last_child:" "\n"
						"fputs(\"├── \", stdout);" "\n"
						"new = malloc(sizeof(*new));" "\n"
						"new->is_last = false;" "\n"
						"new->prev = links;" "\n"
						"break;" "\n"
					"\n"
					"case p_last_child:" "\n"
						"fputs(\"└── \", stdout);" "\n"
						"new = malloc(sizeof(*new));" "\n"
						"new->is_last = true;" "\n"
						"new->prev = links;" "\n"
					"break;" "\n"
				"}" "\n"
				"printf(\"\\e[34m%%s\\e[m (\\e[36m%s\\e[m)\", name);" "\n"
				"#if ZEBU_LINE_NUMBERS" "\n"
				"printf(\" on line %%u through %%u\", ptree->startline, ptree->endline);" "\n"
				"#endif" "\n"
				"printf(\"\\n\");" "\n"
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
						"if (ptree->%s)" "\n"
							"print_token_leaf(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"else" "\n"
							"print_empty_leaf(new ?: links, %s, \"token\", \"%s\");" "\n"
					"", field, prefix, field, field, prefix, field);
					break;
				}
				
				case snt_token_array:
				{
					fprintf(stream, ""
						"if (ptree->%s.n)" "\n"
						"{" "\n"
							"for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
							"{" "\n"
								"char label[%zu + 30];" "\n"
								"snprintf(label, sizeof(label), \"%s[%%u]\", i);" "\n"
								"print_token_leaf(new ?: links, i + 1 < n ? p_not_last_child : %s, label, ptree->%s.data[i]);" "\n"
							"}" "\n"
						"}" "\n"
						"else" "\n"
						"{" "\n"
							"print_empty_leaf(new ?: links, %s, \"token[]\", \"%s\");" "\n"
						"}" "\n"
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
						"if (ptree->%s)" "\n"
							"print_%s_%s(new ?: links, %s, \"%s\", ptree->%s);" "\n"
						"else" "\n"
							"print_empty_leaf(new ?: links, %s, \"%s\", \"%s\");" "\n"
					"", field,
					output_prefix, grammar_chars, prefix, field, field,
					prefix, grammar_chars, field);
					break;
				}
				
				case snt_grammar_array:
				{
					const char* grammar_chars = ele->grammar.name->chars;
					
					fprintf(stream, ""
						"if (ptree->%s.n)" "\n"
						"{" "\n"
							"for (unsigned i = 0, n = ptree->%s.n; i < n; i++)" "\n"
							"{" "\n"
								"char label[%zu + 30];" "\n"
								"snprintf(label, sizeof(label), \"%s[%%u]\", i);" "\n"
								"print_%s_%s(new ?: links, i + 1 < n ? p_not_last_child : %s, label, ptree->%s.data[i]);" "\n"
							"}" "\n"
						"}" "\n"
						"else" "\n"
						"{" "\n"
							"print_empty_leaf(new ?: links, %s, \"%s[]\", \"%s\");" "\n"
						"}" "\n"
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
						"print_scanf_leaf(new ?: links, %s, \"%s\", \"%%%s%c\", ptree->%s);" "\n"
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
							"print_empty_leaf(new ?: links, %s, \"%.*s\", \"%s\");" "\n"
					"", prefix, type->len, type->chars, field);
					
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		
		fprintf(stream, ""
				"free(new);" "\n"
			"}" "\n"
		"");
	}
	
	EXIT;
}
















