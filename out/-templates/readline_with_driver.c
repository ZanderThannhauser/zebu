
#define _GNU_SOURCE

#include <readline/readline.h>
#include <readline/history.h>

#include <errno.h>
#include <limits.h>
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

#ifdef ZEBU_DEBUG
{{TOKEN_IDS_TO_SETS}}
#endif

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef ZEBU_DEBUG
static void escape(char *out, unsigned char in)
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
			sprintf(out, "\\x%02hhX", in);
			break;
	}
}
#endif

int main(int argc, char** argv)
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	#ifdef ZEBU_DEBUG
	setvbuf(stdout, 0, _IONBF, 0);
	#endif
	
	#ifdef ZEBU_DEBUG
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
			#ifdef ZEBU_DEBUG
			char escaped[10];
			#endif
			
			unsigned original_l = l;
			
			char* begin = lexer, *f = NULL;
			
			unsigned a, b;
			unsigned char c;
			
			while (1)
			{
				if ((c = *lexer))
				{
					#ifdef ZEBU_DEBUG
					escape(escaped, c);
					
					ddprintf("lexer: c = '%s' (0x%X)\n", escaped, c);
					#endif
					
					a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
				}
				else
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: c == <EOF>\n");
					#endif
					
					// it would be cool if it would read another line
					// if there wasn't an EOF transition
					a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
				}
				
				b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
				
				#ifdef ZEBU_DEBUG
				ddprintf("lexer: l = %u, a = %u, b = %u\n", l, a, b);
				#endif
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = lexer++;
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: l = %u, t == %u, f = %p (saved)\n", l, t, f);
						#endif
					}
					else
					{
						l = a;
						if (c) lexer++;
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: l == %u\n", l);
						#endif
					}
				}
				else if (b)
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: \"%.*s\"\n", lexer - begin, begin);
					#endif
					
					if (b == 1)
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: whitespace: \"%.*s\"\n", lexer - begin, begin);
						#endif
						l = original_l, begin = lexer, f = NULL;
					}
					else
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: token: \"%.*s\"\n", lexer - begin, begin);
						#endif
						struct {{PREFIX}}_token* token = malloc(sizeof(*token));
						token->refcount = 1;
						token->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);
						token->len = lexer - begin;
						token->data[token->len] = '\0';
						t = b, td = token;
						break;
					}
				}
				else if (f)
				{
					if (t == 1)
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", lexer - begin, begin);
						#endif
						
						assert(!"TODO");
					}
					else
					{
						lexer = f;
						
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: falling back to token: \"%.*s\"\n", lexer - begin, begin);
						#endif
						
						struct {{PREFIX}}_token* token = malloc(sizeof(*token));
						token->refcount = 1;
						token->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);
						token->len = lexer - begin;
						token->data[token->len] = '\0';
						td = token;
						break;
					}
				}
				else
				{
					assert(!"TODO");
				}
			}
		}
		
		yacc.n = 0, data.n = 0, y = 1, push_state(y);
		
		read_token({{PREFIX}}_lexer_starts[y]);
		
		#ifdef ZEBU_DEBUG
		ddprintf("y = %u, t == %u (%s)\n", y, t, {{PREFIX}}_token_names[t]);
		#endif
		
		void* root;
		
		while (yacc.n)
		{
			if (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))
			{
				y = s, push_state(y), push_data(td);
				
				read_token({{PREFIX}}_lexer_starts[y]);
				
				#ifdef ZEBU_DEBUG
				ddprintf("t == %u (%s)\n", t, {{PREFIX}}_token_names[t]);
				#endif
			}
			else if (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
			{
				unsigned g;
				
				void* d;
				
				#ifdef ZEBU_DEBUG
				ddprintf("r = %u\n", r);
				#endif
				
				{{REDUCTION_RULE_SWITCH}}
				
				if (g == {{START_GRAMMAR_ID}})
				{
					free_{{PREFIX}}_token(td);
					yacc.n = 0, root = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					#ifdef ZEBU_DEBUG
					ddprintf("y = %u\n", y);
					#endif
					
					assert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));
					
					s = {{PREFIX}}_gotos[y][g];
					
					#ifdef ZEBU_DEBUG
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
		
		print_zebu_$start(NULL, p_root, "start", root);
		
		free_zebu_$start(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










