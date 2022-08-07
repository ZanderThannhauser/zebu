
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

void* smemdup(const void* src, size_t size)
{
	void* new = smalloc(size);
	memcpy(new, src, size);
	return new;
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

struct value
{
	unsigned shifton;
	enum {
		vk_token,
		vk_grammar,
		vk_EOF,
	} kind;
	union {
		struct {
			unsigned char* data;
			unsigned n;
		} t;
		struct {
			const char* name;
			struct value** values;
			unsigned n;
		} g;
	};
};

struct value* new_token(unsigned shifton, unsigned char* data, unsigned n)
{
	struct value* value = smalloc(sizeof(*value));
	
	value->shifton = shifton;
	
	value->kind = vk_token;
	
	value->t.data = smemdup(data, sizeof(*data) * n);
	value->t.n = n;
	
	return value;
}

struct value* new_EOF_token(unsigned shifton)
{
	struct value* value = smalloc(sizeof(*value));
	
	value->shifton = shifton;
	
	value->kind = vk_EOF;
	
	return value;
}

struct lexer { unsigned char* data, n, cap; };

struct value* read_token(struct lexer* lexer, FILE* stream, unsigned state)
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
			if (!lexer->n)
			{
				lexer->n = 0;
				return new_EOF_token(accept);
			}
			else
			{
				struct value* retval = new_token(accept, lexer->data, lexer->n - 1);
				lexer->n = 0;
				if (c != EOF) lexer->data[lexer->n++] = c;
				return retval;
			}
		}
		else if (token)
		{
			struct value* retval = new_token(token, lexer->data, fallback);
			memmove(lexer->data, lexer->data + fallback, lexer->n - fallback);
			lexer->n -= fallback;
			return retval;
		}
		else
		{
			assert(!"168");
		}
	}
}

struct value* new_grammar(
	unsigned shifton,
	const char* name,
	struct value** values,
	unsigned n_values)
{
	struct value* v = smalloc(sizeof(*v));
	
	v->shifton = shifton;
	
	v->kind = vk_grammar;
	
	v->g.name = name;
	v->g.values = smemdup(values, sizeof(*values) * n_values);
	v->g.n = n_values;
	
	return v;
}

struct value* parse(FILE* stream)
{
	struct { unsigned* data, n, cap; } stack = {};
	struct { struct value** data; unsigned n, cap; } values = {};
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
	
	void push_value(struct value* v)
	{
		if (values.n + 1 >= values.cap)
		{
			values.cap = values.cap << 1 ?: 1;
			values.data = realloc(values.data, sizeof(*values.data) * values.cap);
		}
		values.data[values.n++] = v;
	}
	
	push(1);
	
	struct value* g = NULL, *t = read_token(&lexer, stream, 1);
	
	while (1)
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
		
		if (values.n)
		{
			for (unsigned i = 0, n = values.n; i < n; i++)
			{
				struct value* v = values.data[i];
				switch (v->kind) {
					case vk_token: printf("\"%.*s\"", v->t.n, v->t.data); break;
					case vk_grammar: printf("%s", v->g.name); break;
					case vk_EOF: printf("<EOF>"); break;
				}
				
				if (i + 1 < n)
					printf(" | ");
			}
			puts("");
		}
		
		unsigned y = stack.data[stack.n - 1], s, r;
		
		unsigned w = g ? g->shifton : t ? t->shifton : 0;
		if (y < N(<PREFIX>_shifts) && w < N(*<PREFIX>_shifts) && (s = <PREFIX>_shifts[y][w]))
		{
			push_value(g ?: t);
			push(s);
			if (g) g = NULL;
			else t = read_token(&lexer, stream, <PREFIX>_starts[s]);
		}
		else if (y < N(<PREFIX>_reduces) && w < N(*<PREFIX>_reduces) && (r = <PREFIX>_reduces[y][w]))
		{
			assert(!g);
			if (r == start_grammar_id)
			{
				free(t);
				
				g = new_grammar(r, zebu_grammar_names[r], values.data, values.n);
				
				free(stack.data);
				free(lexer.data);
				free(values.data);
				
				return g;
			}
			else
			{
				unsigned p = <PREFIX>_popcounts[y][w];
				g = new_grammar(r, zebu_grammar_names[r], values.data + values.n - p, p);
				stack.n -= p, values.n -= p;
			}
		}
		else
		{
			assert(!"266");
		}
	}
}

void dotout(struct value* value, FILE* stream)
{
	switch (value->kind)
	{
		case vk_token:
		{
			fprintf(stream, "\"%p\" [ label = \"", value);
			
			for (unsigned i = 0, u, n = value->t.n; i < n; i++)
				switch ((u = value->t.data[i]))
				{
					case '\n': fprintf(stream, "&#%u;&#%u;&#%u;", '\\', '\\', 'n'); break;
					case '\t': fprintf(stream, "&#%u;&#%u;&#%u;", '\\', '\\', 't'); break;
					default: fprintf(stream, "&#%u;", u); break;
				}
			
			fprintf(stream, "\" ];\n");
			
			free(value->t.data);
			break;
		}
		
		case vk_grammar:
		{
			fprintf(stream, "\"%p\" [ label = \"%s\" ];", value, value->g.name);
			
			for (unsigned i = 0, n = value->g.n; i < n; i++)
			{
				struct value* e = value->g.values[i];
				dotout(e, stream);
				fprintf(stream, "\"%p\" -> \"%p\"\n", value, e);
			}
			
			free(value->g.values);
			break;
		}
		
		case vk_EOF:
			fprintf(stream, "\"%p\" [ label = \"<EOF>\" ];", value);
			break;
	}
	
	free(value);
}

int main(int argc, char* const* argv)
{
	struct cmdln* cmdln = process_cmdln(argc, argv);
	
	FILE* input = sfopen(cmdln->input, "r");
	
	struct value* ptree = parse(input);
	
	fclose(input);
	
	FILE* output = sfopen(cmdln->output, "w");
	
	fprintf(output, "digraph {\n");
	
	fprintf(output, "rankdir = LR;\n");
	
	fprintf(output, "node [shape = box];\n");
	
	dotout(ptree, output);
	
	fprintf(output, "}\n");
	
	fclose(output);
	
	free(cmdln);
	
	return 0;
}


















