
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <yacc/structinfo/struct.h>
#include <yacc/structinfo/foreach.h>
#include <yacc/structinfo/is_empty.h>

#include "struct.h"
#include "print_source.h"

void reductioninfo_print_source(
	struct reductioninfo* this,
	struct structinfo* structinfo,
	const char* grammar,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	switch (this->kind)
	{
		case rik_token:
		{
			bool once = true;
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct string* name, enum structinfo_node_type type, struct string* _)
				{
					switch (type)
					{
						case snt_token_scalar:
						{
							if (once)
							{
								fprintf(stream, ""
									"\t" "\t" "free_token(value->%s), value->%s = data.data[--yacc.n, --data.n];" "\n"
								"", name->chars, name->chars);
								once = false;
							}
							else
							{
								fprintf(stream, ""
									"\t" "\t" "free_token(value->%s), value->%s = inc_token(data.data[data.n]);" "\n"
								"", name->chars, name->chars);
							}
							break;
						}
						
						case snt_token_array:
						{
							if (once)
							{
								fprintf(stream, ""
									"\t" "\t" "if (value->%s.n == value->%s.cap)" "\n"
									"\t" "\t" "{" "\n"
									"\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
									"\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
									"\t" "\t" "}" "\n"
									"\t" "\t" "memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
									"\t" "\t" "value->%s.data[0] = data.data[--yacc.n, --data.n], value->%s.n++;" "\n"
								"", name->chars, name->chars,
								name->chars, name->chars,
								name->chars, name->chars, name->chars, name->chars,
								name->chars, name->chars, name->chars, name->chars,
								name->chars, name->chars);
								once = false;
							}
							else
							{
								TODO;
							}
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			if (structinfo_is_empty(this->structinfo))
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
			
			const char* datatype = this->grammar->chars;
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct string* name, enum structinfo_node_type type, struct string* grammar)
				{
					const char* name_chars = name->chars;
					
					switch (type)
					{
						case snt_grammar_scalar:
						{
							if (once)
							{
								fprintf(stream, ""
									"\t" "\t" "free_%s_%s(value->%s), value->%s = data.data[--yacc.n, --data.n];" "\n"
								"", prefix, datatype, name_chars, name_chars);
								once = false;
							}
							else
							{
								TODO;
								#if 0
								fprintf(stream, ""
									"\t" "\t" "free_%s(value->%s), value->%s = inc_%s_tree(data.data[data.n]);" "\n"
								"", type, tag->chars, tag->chars, type);
								#endif
							}
							break;
						}
						
						case snt_grammar_array:
						{
							if (once)
							{
								fprintf(stream, ""
									"\t" "\t" "if (value->%s.n == value->%s.cap)" "\n"
									"\t" "\t" "{" "\n"
									"\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
									"\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
									"\t" "\t" "}" "\n"
									"\t" "\t" "memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
									"\t" "\t" "value->%s.data[0] = data.data[--yacc.n, --data.n], value->%s.n++;" "\n"
								"", name_chars, name_chars,
								name_chars, name_chars,
								name_chars, name_chars, name_chars, name_chars,
								name_chars, name_chars, name_chars, name_chars,
								name_chars, name_chars);
								once = false;
							}
							else
							{
								TODO;
							}
							break;
						}
						
						default:
							TODO;
							break;
					}
					
				}
				runme;
			}));
			
			if (structinfo_is_empty(this->structinfo))
			{
				fprintf(stream, ""
					"\t" "\t" "free_%s_%s(data.data[--yacc.n, --data.n]);" "\n"
				"", prefix, datatype);
			}
			
			break;
		}
		
		case rik_trie:
		{
			dpvs(this->grammar);
			
			assert(this->grammar);
			
			fprintf(stream, ""
				"\t" "\t" "{" "\n"
				"\t" "\t" "\t" "struct %s_%s* trie = data.data[--yacc.n, --data.n];" "\n"
			"", prefix, grammar);
			
			structinfo_foreach(structinfo, ({
				void runme(struct string* name, enum structinfo_node_type type, struct string* grammar)
				{
					const char* const name_chars = name->chars;
					
					switch (type)
					{
						case snt_token_scalar:
						{
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s) { free_token(value->%s); value->%s = inc_token(trie->%s); }" "\n"
							"", name_chars, name_chars, name_chars, name_chars);
							break;
						}
						
						case snt_token_array:
						{
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s.n)"
								"\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
								"\t" "\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "\t" "\t" "}" "\n"
								"\t" "\t" "\t" "\t" "memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "\t" "\t" "for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data[i] = inc_token(trie->%s.data[i]);" "\n"
								"\t" "\t" "\t" "\t" "value->%s.n += trie->%s.n;" "\n"
								"\t" "\t" "\t" "}" "\n"
							"", name_chars,
							name_chars, name_chars, name_chars,
							name_chars, name_chars,
							name_chars, name_chars, name_chars, name_chars,
							name_chars, name_chars, name_chars, name_chars, name_chars,
							name_chars,
							name_chars, name_chars,
							name_chars, name_chars);
							break;
						}
						
						case snt_grammar_scalar:
						{
							const char* const grammar_chars = grammar->chars;
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s) { free_%s_%s(value->%s); value->%s = inc_%s_%s(trie->%s); }" "\n"
							"", name_chars, prefix, grammar_chars, name_chars, name_chars, prefix, grammar_chars, name_chars);
							break;
						}
						
						case snt_grammar_array:
						{
							const char* const grammar_chars = grammar->chars;
							
							fprintf(stream, ""
								"\t" "\t" "\t" "if (trie->%s.n)" "\n"
								"\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
								"\t" "\t" "\t" "\t" "{" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"\t" "\t" "\t" "\t" "}" "\n"
								"\t" "\t" "\t" "\t" "memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"\t" "\t" "\t" "\t" "for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
								"\t" "\t" "\t" "\t" "\t" "value->%s.data[i] = inc_%s_%s(trie->%s.data[i]);" "\n"
								"\t" "\t" "\t" "\t" "value->%s.n += trie->%s.n;" "\n"
								"\t" "\t" "\t" "}" "\n"
							"", name_chars,
							name_chars, name_chars, name_chars,
							name_chars, name_chars,
							name_chars, name_chars, name_chars, name_chars,
							name_chars, name_chars, name_chars, name_chars, name_chars,
							name_chars,
							name_chars, prefix, grammar_chars, name_chars,
							name_chars, name_chars);
							break;
						}
						
						case snt_user_defined:
							break;
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			fprintf(stream, ""
				"\t" "\t" "\t" "free_%s_%s(trie);" "\n"
				"\t" "\t" "}" "\n"
			"", prefix, grammar);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(this->prev, structinfo, grammar, prefix, stream);
	}
	
	EXIT;
}




















