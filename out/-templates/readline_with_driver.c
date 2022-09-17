
#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

{{LEXER_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

{{PARSE_TREE_STRUCTS}}

{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

#ifdef DEBUG
{{TOKEN_IDS_TO_SETS}}
#endif

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef DEBUG
static void escape(char *out, char in)
{
	switch (in)
	{
		case ' ':
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '=':
		case '|':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}
#endif

int main()
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	#ifdef DEBUG
	void ddprintf(const char* fmt, ...)
	{
		for (unsigned i = 0, n = yacc.n; i < n; i++)
			printf("%u ", yacc.data[i]);
		
		printf("| ");
		
		va_list va;
		va_start(va, fmt);
		vprintf(fmt, va);
		va_end(va);
	}
	#endif
	
	void push_state(unsigned state)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		
		yacc.data[yacc.n++] = state;
	}
	
	void push_data(void* element)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		
		data.data[data.n++] = element;
	}
	
	for (char* line; (line = readline(">>> "));)
	{
		char* lexer = (void*) line;
		
		unsigned y, s, r, t;
		
		void* td;
		
		void read_token(unsigned l)
		{
			#ifdef DEBUG
			char escaped[10];
			#endif
			
			unsigned original_l = l;
			
			char* begin = lexer, *f = NULL;
			
			unsigned a, b, c;
			
			while (1)
			{
				if ((c = *lexer))
				{
					#ifdef DEBUG
					escape(escaped, c);
					
					ddprintf("c = '%s' (0x%X)\n", escaped, c);
					#endif
					
					a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
				}
				else
				{
					#ifdef DEBUG
					ddprintf("c == <EOF>\n");
					#endif
					
					// it would be cool if it would read another line
					// if there wasn't an EOF transition
					a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
				}
				
				b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
				
				#ifdef DEBUG
				ddprintf("lexer: %u: a = %u, b = %u\n", l, a, b);
				#endif
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = lexer++;
						#ifdef DEBUG
						ddprintf("l = %u, t == %u, f = %p (saved)\n", l, t, f);
						#endif
					}
					else
					{
						l = a;
						if (c) lexer++;
						#ifdef DEBUG
						ddprintf("lexer: l == %u\n", l);
						#endif
					}
				}
				else if (b)
				{
					#ifdef DEBUG
					ddprintf("lexer: \"%.*s\"\n", lexer - begin, begin);
					#endif
					
					if (b == 1)
					{
						#ifdef DEBUG
						ddprintf("lexer: whitespace\n");
						#endif
						l = original_l, begin = lexer, f = NULL;
					}
					else
					{
						struct token* token = malloc(sizeof(*token));
						token->refcount = 1;
						token->data = memcpy(malloc(lexer - begin), begin, lexer - begin);
						token->len = lexer - begin;
						t = b, td = token;
						break;
					}
				}
				else if (f)
				{
					assert(!"172" || f);
					#if 0
					process_token(t);
					l = {{PREFIX}}_starts[yacc.data[yacc.n - 1]], i = f, t = 0;
					ddprintf("l == %u, i = %u, t = %u\n", l, i, t);
					#endif
				}
				else
				{
					assert(!"TODO");
				}
			}
		}
		
		yacc.n = 0, data.n = 0, y = 1, push_state(y);
		
		read_token({{PREFIX}}_lexer_starts[y]);
		
		#ifdef DEBUG
		ddprintf("y = %u, t == %u (%s)\n", y, t, {{PREFIX}}_token_names[t]);
		#endif
		
		void* root;
		
		while (yacc.n)
		{
			if (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))
			{
				y = s, push_state(y), push_data(td);
				
				read_token({{PREFIX}}_lexer_starts[y]);
				
				#ifdef DEBUG
				ddprintf("t == %u (%s)\n", t, {{PREFIX}}_token_names[t]);
				#endif
			}
			else if (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
			{
				unsigned g;
				
				void* d;
				
				#ifdef DEBUG
				ddprintf("r = %u\n", r);
				#endif
				
				{{REDUCTIONRULE_SWITCH}}
				
				if (g == {{START_GRAMMAR_ID}})
				{
					free_token(td);
					yacc.n = 0, root = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					#ifdef DEBUG
					ddprintf("y = %u\n", y);
					#endif
					
					assert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));
					
					s = {{PREFIX}}_gotos[y][g];
					
					#ifdef DEBUG
					ddprintf("s = %u\n", s);
					#endif
					
					y = s, push_state(y), push_data(d);
				}
			}
			else
			{
				assert(!"190");
			}
		}
		
		assert(!data.n);
		
		print_zebu_$start_ptree(NULL, p_root, "start", root);
		
		free_zebu_$start_ptree(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










