
#define _GNU_SOURCE

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

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

struct lexer { unsigned char* data; unsigned n, cap; };

unsigned read_token(struct lexer* lexer, FILE* stream, unsigned state)
{
	void append(unsigned char c)
	{
		while (lexer->n + 1 >= lexer->cap)
		{
			lexer->cap = lexer->cap << 1 ?: 1;
			lexer->data = realloc(lexer->data, lexer->cap);
		}
		
		lexer->data[lexer->n++] = c;
	}
	
	unsigned i = 0;
	
	unsigned token = 0, fallback;
	
	while (1)
	{
		unsigned next, accept, c;
		
		if (i < lexer->n)
		{
			c = lexer->data[i];
			
			next = 0
				?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)
				?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);
		}
		else if ((c = getc(stream)) != EOF)
		{
			append(c);
			
			next = 0
				?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)
				?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);
		}
		else
		{
			c = EOF;
			next = state < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[state] : 0;
		}
		
		accept = (state < N(<PREFIX>_accepts) ? <PREFIX>_accepts[state] : 0);
		
		if (next)
		{
			if (accept)
			{
				state = next, token = accept, fallback = i++;
			}
			else
			{
				state = next, i++;
			}
		}
		else if (accept)
		{
			lexer->n = 0;
			if (c != EOF) lexer->data[lexer->n++] = c;
			return accept;
		}
		else if (token)
		{
			memmove(lexer->data, lexer->data + fallback, lexer->n - fallback);
			lexer->n -= fallback;
			return token;
		}
		else
		{
			assert(!"168");
		}
	}
}

void parse(FILE* stream)
{
	struct { unsigned* data, n, cap; } stack = {};
	struct lexer lexer = {};
	
	void push(unsigned y)
	{
		if (stack.n + 1 >= stack.cap)
		{
			stack.cap = stack.cap << 1 ?: 1;
			stack.data = realloc(stack.data, sizeof(*stack.data) * stack.cap);
		}
		stack.data[stack.n++] = y;
	}
	
	push(1);
	
	unsigned g = 0, t = read_token(&lexer, stream, 1);
	
	while (stack.n)
	{
		unsigned y = stack.data[stack.n - 1], s, r;
		
		if (y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (s = <PREFIX>_shifts[y][g ?: t]))
		{
			push(s);
			if (g) g = 0;
			else t = read_token(&lexer, stream, <PREFIX>_starts[s]);
		}
		else if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (r = <PREFIX>_reduces[y][t]))
		{
			if (r == start_grammar_id)
				stack.n = 0;
			else
				stack.n -= <PREFIX>_popcounts[y][t], g = r;
		}
		else
		{
			assert(!"266");
		}
	}
	
	free(stack.data);
	free(lexer.data);
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
	
	parse(input);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















