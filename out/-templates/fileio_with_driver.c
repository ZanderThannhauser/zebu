
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
		case '/':
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
		
		case '\'': *out++ = '\\', *out++ = '\'', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}
#endif

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
				ddprintf("lexer: cap == %u\n", lexer.cap);
				#endif
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		unsigned original_l = l, i = 0, a, b, c, f = 0;
		
		t = 0;
		
		#ifdef DEBUG
		ddprintf("lexer: \"%.*s\": l = %u\n", lexer.n, lexer.data, l);
		#endif
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				#ifdef DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%X) (from cache)\n", escaped, c);
				#endif
				
				a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
			}
			else if ((c = getc(stream)) != EOF)
			{
				append(c);
				
				#ifdef DEBUG
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("lexer: c = '%s' (0x%X)\n", escaped, c);
				#endif
				
				a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				#ifdef DEBUG
				ddprintf("lexer: c = <EOF>\n");
				#endif
				
				a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
			}
			
			b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
			
			#ifdef DEBUG
			ddprintf("lexer: \"%.*s\" (%u): a = %u, b = %u\n", lexer.n, lexer.data, i, a, b);
			#endif
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = i++;
					#ifdef DEBUG
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
				else
				{
					l = a, i++;
					#ifdef DEBUG
					ddprintf("lexer: l = %u\n", l);
					#endif
				}
			}
			else if (b)
			{
				#ifdef DEBUG
				ddprintf("lexer: token: \"%.*s\"\n", i, lexer.data);
				#endif
				
				if (!lexer.n)
				{
					#ifdef DEBUG
					ddprintf("lexer: EOF.\n");
					#endif
					t = b, td = NULL;
					break;
				}
				else if (b == 1)
				{
					#ifdef DEBUG
					ddprintf("lexer: whitespace: \"%.*s\"\n", i, lexer.data);
					#endif
					
					l = original_l, t = 0;
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i, i = 0;
				}
				else
				{
					#ifdef DEBUG
					ddprintf("lexer: i = %u\n", i);
					#endif
					
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(i), lexer.data, i);
					token->len = i;
					t = b, td = token;
					
					memmove(lexer.data, lexer.data + i, lexer.n - i), lexer.n -= i;
					break;
				}
			}
			else if (f)
			{
				if (t == 1)
				{
					#ifdef DEBUG
					ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", f, lexer.data);
					#endif
					
					l = original_l, t = 0;
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0, i = 0;
				}
				else
				{
					#ifdef DEBUG
					ddprintf("lexer: falling back to token: \"%.*s\"\n", f, lexer.data);
					#endif
					
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(f), lexer.data, f);
					token->len = f;
					td = token;
					
					memmove(lexer.data, lexer.data + f, lexer.n - f), lexer.n -= f, f = 0;
					break;
				}
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
	
	#ifdef DEBUG
	print_zebu_$start_ptree(NULL, p_root, "start", root);
	#endif
	
	free_zebu_$start_ptree(root);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















