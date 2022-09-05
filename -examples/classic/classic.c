#include "classic.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define N(array) (sizeof(array) / sizeof(*array))

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

int main()
{
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data, n, cap; } data = {};
	
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

	void push(unsigned ystate)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		
		yacc.data[yacc.n++] = ystate;
	}
	
	unsigned current_token;
	
	void read_token(unsigned start)
	{
		assert(!"92");
		
		#if 0
		unsigned i = l.n, n = i, l = lstate;
		unsigned a, b, c, f = 0, t = t;
		
		char escaped[10];
		
		while (1)
		{
			assert(i <= n + 1);
			
			if (i < n)
			{
				c = l.data[i];
				
				escape(escaped, c);
				
				ddprintf(this, "c = %s (0x%X)\n", escaped, c);
			
				a = (c < N(*{{zebu_lexer) ? {{zebu_lexer[l][c] : 0) ?: (l < N( {{zebu_defaults) ? {{zebu_defaults[l] : 0);
			}
			else
			{
				ddprintf(this, "c == <EOF>\n");
				a = l < N({{zebu_EOFs) ? {{zebu_EOFs[l] : 0;
			}
			
			b = (l < N({{zebu_accepts) ? {{zebu_accepts[l] : 0);
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = i++;
					ddprintf(this, "l = %u, t == %u, f = %u (saved)\n", l, t, f);
				}
				else
				{
					l = a, i++;
					ddprintf(this, "l == %u\n", l);
				}
			}
			else if (b)
			{
				process_token(this, b);
				
				if (!yacc.n) break;
				
				l = {{zebu_starts[yacc.data[yacc.n - 1]], f = i, t = 0;
				ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
			}
			else if (t)
			{
				process_token(this, t);
				l = {{zebu_starts[yacc.data[yacc.n - 1]], i = f, t = 0;
				ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
			}
			else
			{
				assert(!"TODO");
			}
		}
		#endif
	}
	
	for (char* line; (line = readline(">>> "));)
	{
		yacc.n = 0, l.n = 0;
		
		push(1);
		
		ddprintf(this, "y = %u, l == %u\n", 1, 1);
		
		unsigned Y = 1, t = read_token({{zebu_starts[Y]), s, r;
		
		while (yacc.n)
		{
			TODO;
			#if 0
			if (Y < N({{zebu_shifts) && t < N(*{{zebu_shifts) && (s = {{zebu_shifts[y][t]))
			{
				Y = s, push(Y);
				t = read_token({{zebu_starts[Y]);
			}
			else if (Y < N({{zebu_reduces) && t < N(*{{zebu_reduces) && (r = {{zebu_reduces[y][t]))
			{
				unsigned g, popcount;
				
				{{// We'll burn that bridge when we get there!

				
				if (g == start_grammar_id)
				{
					yacc.n = 0;
				}
				else
				{
					yacc.n -= popcount;
					
					Y = yacc.data[yacc.n - 1];
					
					ddprintf(this, "Y = %u\n", Y);
					
					assert(Y < N({{zebu_gotos) && g < N(*{{zebu_gotos));
					
					s = {{zebu_gotos[y][g];
					
					ddprintf(this, "s = %u\n", s);
					
					Y = s, push(this, Y);
				}
			}
			else
			{
				assert(!"190");
			}
			#endif
		}
		
		puts("accepted!");
		
		add_history(line);
		
		free(line);
	}
	
	free(yacc.data);
	
	return 0;
}










