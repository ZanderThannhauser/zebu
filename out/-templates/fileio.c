
#define _GNU_SOURCE

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#define argv0 (program_invocation_name)

#define N(array) (sizeof(array) / sizeof(*array))

void* smalloc(size_t size)
{
	void* ptr = malloc(size);
	if (!ptr)
	{
		fprintf(stderr, "%s: malloc(%lu): %m\n", argv0, size);
		exit(1);
	}
	return ptr;
}

void* srealloc(void* ptr, size_t size)
{
	assert(!"TODO");
}

FILE* sfopen(const char* path, const char* mode)
{
	FILE* stream = fopen(path, mode);
	
	if (!stream)
	{
		fprintf(stderr, "%s: fopen(\"%s\", \"%s\"): %m\n", argv0, path, mode);
		exit(1);
	}
	
	return stream;
}

struct cmdln
{
	const char* input;
	const char* output;
};

void usage(int code)
{
	fprintf(stderr, "usage: "
		"%s <path/to/input/file> -o <path/to/output/file.dot>\n", argv0);
	exit(code);
}

struct cmdln* process_cmdln(int argc, char* const* argv)
{
	int opt;
	
	const char* input = NULL;
	const char* output = NULL;
	
	while ((opt = getopt(argc, argv, "ho:")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			case 'o':
				output = optarg;
				break;
			
			default:
				usage(1);
		}
	}
	
	input = argv[optind++];
	
	if (!input || !output)
		usage(1);
	
	struct cmdln* retval = smalloc(sizeof(*retval));
	retval->input = input;
	retval->output = output;
	return retval;
}

struct lexer { unsigned char* data, n, cap; };

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
		
		printf("\"%.*s\"\n", lexer->n, lexer->data);
		
		if (i < lexer->n)
		{
			c = lexer->data[i];
			
			next = 0
				?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)
				?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);
		}
		else if ((c = getc(stream)) != EOF)
		{
			printf("c == %c\n", c);
			
			append(c);
			
			next = 0
				?: (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[state][c] : 0)
				?: (state < N( <PREFIX>_defaults) ? <PREFIX>_defaults[state] : 0);
		}
		else
		{
			c = EOF;
			printf("c == <EOF>\n");
			next = state < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[state] : 0;
		}
		
		accept = (state < N(<PREFIX>_accepts) ? <PREFIX>_accepts[state] : 0);
		
		printf("next == %u\n", next);
		printf("accept == %u\n", accept);
		
		if (next)
		{
			if (accept)
			{
				state = next, token = accept, fallback = i++;
				
				printf("token == %u\n", token);
				printf("fallback == %u\n", fallback);
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
			printf("n == %u\n", lexer->n);
			printf("fallback == %u\n", fallback);
			printf("\"%.*s\"\n", lexer->n, lexer->data);
			memmove(lexer->data, lexer->data + fallback, lexer->n - fallback);
			lexer->n -= fallback;
			printf("\"%.*s\"\n", lexer->n, lexer->data);
			return token;
		}
		else
		{
			assert(!"168");
		}
	}
}

struct value
{
	enum {
		vk_token,
		vk_grammar,
	} kind;
	union {
		
	};
};

struct value* parse(FILE* stream)
{
	struct { unsigned* data, n, cap; } stack = {};
	struct lexer lexer = {};
	
	void push(unsigned y)
	{
		printf("push(%u);\n", y);
		
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
		{
			for (unsigned i = 0, n = stack.n; i < n; i++)
			{
				printf("%u", stack.data[i]);
				if (i + 1 < n)
					printf(" | ");
			}
			puts("");
		}
		
		unsigned y = stack.data[stack.n - 1], s, r;
		printf("y = %u, g = %u, t = %u\n", y, g, t);
		
		if (y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (s = <PREFIX>_shifts[y][g ?: t]))
		{
			push(s);
			if (g) g = 0;
			else t = read_token(&lexer, stream, <PREFIX>_starts[s]);
		}
		else if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (r = <PREFIX>_reduces[y][t]))
		{
			stack.n -= <PREFIX>_popcounts[y][t], g = r;
		}
		else
		{
			assert(!"266");
		}
	}
	
	free(stack.data);
	free(lexer.data);
	
	return NULL;
}

void dotout(struct value* value, FILE* stream)
{
	assert(!"TODO");
}

int main(int argc, char* const* argv)
{
	struct cmdln* cmdln = process_cmdln(argc, argv);
	
	FILE* input = sfopen(cmdln->input, "r");
	
	struct value* ptree = parse(input);
	
	fclose(input);
	
	FILE* output = sfopen(cmdln->output, "w");
	
	dotout(ptree, output);
	
	fclose(output);
	
	free(cmdln);
	
	return 0;
}


















