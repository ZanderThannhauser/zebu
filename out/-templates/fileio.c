
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

{{LEXER_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

#ifdef DEBUG
{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}
#endif

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef DEBUG
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
			sprintf(out, "\\x%02X", in);
			break;
	}
}
#endif

struct zebu_$start* {{PREFIX}}_parse(FILE* stream)
{
	void* root;
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data; unsigned n, cap; } data = {};
	struct { unsigned char* data; unsigned n, cap; } lexer = {};
	
	void push_state(unsigned y)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		yacc.data[yacc.n++] = y;
	}
	
	void push_data(void* d)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		data.data[data.n++] = d;
	}
	
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
	
	unsigned y, t, s, r;
	void* td;
	
	void read_token(unsigned l)
	{
		void append(unsigned char c)
		{
			while (lexer.n + 1 >= lexer.cap)
			{
				lexer.cap = lexer.cap << 1 ?: 1;
				#ifdef DEBUG
				ddprintf("lexer.cap == %u\n", lexer.cap);
				#endif
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		unsigned original_l = l, i = 0, a, b, c;
		
		t = 0;
		
		#ifdef DEBUG
		ddprintf("l = %u\n", l);
		#endif
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				#ifdef DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X) (from cache)\n", escaped, c);
				#endif
				
				assert(!"163");
				#if 0
				next = 0
					?: (state < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[state][c] : 0)
					?: (state < N({{PREFIX}}_defaults) ? {{PREFIX}}_defaults[state] : 0);
				#endif
			}
			else if ((c = getc(stream)) != EOF)
			{
				append(c);
				
				#ifdef DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X)\n", escaped, c);
				#endif
				
				a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				#ifdef DEBUG
				ddprintf("c = <EOF>\n");
				#endif
				
				a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
			}
			
			b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
			
			#ifdef DEBUG
			ddprintf("a = %u, b = %u\n", a, b);
			#endif
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, i++;
					#ifdef DEBUG
					ddprintf("l = %u\n", l);
					#endif
				}
				else
				{
					l = a, i++;
					#ifdef DEBUG
					ddprintf("l = %u\n", l);
					#endif
				}
			}
			else if (b)
			{
				if (c != EOF)
				{
					lexer.n--, ungetc(c, stream);
				}
				
				#ifdef DEBUG
				ddprintf("lexer: \"%.*s\"\n", lexer.n, lexer.data);
				#endif
				
				if (b == 1)
				{
					#ifdef DEBUG
					ddprintf("lexer: whitespace.\n");
					#endif
					l = original_l, t = 0, lexer.n = 0;
				}
				else
				{
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(lexer.n), lexer.data, lexer.n);
					token->len = lexer.n;
					t = b, td = token, lexer.n = 0;
					break;
				}
			}
			else if (t)
			{
				assert(!"235");
				#if 0
				memmove(lexer.data, lexer.data + fallback, lexer.n - fallback);
				lexer.n -= fallback;
				return token;
				#endif
			}
			else
			{
				assert(!"168");
			}
		}
	}
	
	push_state(1), y = 1, read_token(1);
	
	#ifdef DEBUG
	ddprintf("y = %u, t = %u\n", y, t);
	#endif
	
	while (yacc.n)
	{
		if (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))
		{
			#ifdef DEBUG
			ddprintf("s == %u\n", s);
			#endif
			
			y = s, push_state(y), push_data(td);
			
			read_token({{PREFIX}}_lexer_starts[y]);
			
			#ifdef DEBUG
			ddprintf("t = %u\n", t);
			#endif
		}
		else if (y < N( {{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
		{
			#ifdef DEBUG
			ddprintf("r == %u\n", r);
			#endif
			
			unsigned g;
			void* d;
			
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
			assert(!"266");
		}
	}
	
	#ifdef DEBUG
	print_{{PREFIX}}_$start_ptree(NULL, p_root, "start", root);
	#endif
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return root;
}

















