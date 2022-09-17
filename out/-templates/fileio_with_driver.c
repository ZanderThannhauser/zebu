
#define _GNU_SOURCE

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

{{PARSE_TREE_STRUCTS}}

#ifdef DEBUG
{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}
#endif

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

#define argv0 (program_invocation_name)

#define N(array) (sizeof(array) / sizeof(*array))

struct cmdln
{
	const char* input;
};

void usage(int code)
{
	fprintf(stderr, "usage: %s <path/to/input/file>\n", argv0);
	exit(code);
}

struct cmdln* process_cmdln(int argc, char* const* argv)
{
	int opt;
	
	const char* input = NULL;
	
	while ((opt = getopt(argc, argv, "h")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			default:
				usage(1);
		}
	}
	
	input = argv[optind++];
	
	if (!input)
		usage(1);
	
	struct cmdln* retval = malloc(sizeof(*retval));
	assert(retval);
	retval->input = input;
	return retval;
}

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

void* parse(FILE* stream)
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
	
	unsigned y, t, s, r;
	void* td;
	
	void read_token(unsigned l)
	{
		void append(unsigned char c)
		{
			while (lexer.n + 1 >= lexer.cap)
			{
				lexer.cap = lexer.cap << 1 ?: 1;
				ddprintf("lexer.cap == %u\n", lexer.cap);
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		unsigned original_l = l, i = 0, a, b, c;
		
		t = 0;
		
		ddprintf("l = %u\n", l);
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X) (from cache)\n", escaped, c);
				
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
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X)\n", escaped, c);
				
				a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				ddprintf("c = <EOF>\n");
				
				a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
			}
			
			b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
			
			ddprintf("a = %u, b = %u\n", a, b);
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, i++;
					ddprintf("l = %u\n", l);
				}
				else
				{
					l = a, i++;
					ddprintf("l = %u\n", l);
				}
			}
			else if (b)
			{
				if (c != EOF)
				{
					lexer.n--, ungetc(c, stream);
				}
				
				ddprintf("lexer: \"%.*s\"\n", lexer.n, lexer.data);
				
				if (b == 1)
				{
					ddprintf("lexer: whitespace.\n");
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
	
	ddprintf("y = %u, t = %u\n", y, t);
	
	while (yacc.n)
	{
		if (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))
		{
			ddprintf("s == %u\n", s);
			
			y = s, push_state(y), push_data(td);
			
			read_token({{PREFIX}}_lexer_starts[y]);
			
			ddprintf("t = %u\n", t);
		}
		else if (y < N( {{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
		{
			ddprintf("r == %u\n", r);
			
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
				
				ddprintf("y = %u\n", y);
				
				assert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));
				
				s = {{PREFIX}}_gotos[y][g];
				
				ddprintf("s = %u\n", s);
				
				y = s, push_state(y), push_data(d);
			}
		}
		else
		{
			assert(!"266");
		}
	}
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return root;
}

int main(int argc, char* const* argv)
{
	struct cmdln* cmdln = process_cmdln(argc, argv);
	
	FILE* input = fopen(cmdln->input, "r");
	
	if (!input)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, cmdln->input),
		exit(1);
	}
	
	void* root = parse(input);
	
	print_zebu_$start_ptree(NULL, p_root, "start", root);
	
	free_zebu_$start_ptree(root);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















