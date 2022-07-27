
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "output.h"

struct zebu_state
{
	unsigned* data, n, cap;
	unsigned lstate;
};

static void push(struct zebu_state* this, unsigned ystate)
{
	if (this->n + 1 >= this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = realloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = ystate;
}

static void ddprintf(struct zebu_state* this, const char* fmt, ...)
{
	for (unsigned i = 0, n = this->n; i < n; i++)
		printf("%u ", this->data[i]);
	
	printf("| ");
	
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}

struct zebu_state* new_zebu_state()
{
	struct zebu_state* this = malloc(sizeof(*this));
	
	assert(this);
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	push(this, 1); // 1 is the start state
	
	this->lstate = 1;
	
	return this;
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct zebu_state* this, unsigned t)
{
	unsigned b, d, y = this->data[this->n - 1];
	
	ddprintf(this, "t == %u\n", t);
	
	while (!(y < N(shifts) && t < N(*shifts) && (b = shifts[y][t])))
	{
		if (y < N(reduces) && t < N(*reduces) && (b = reduces[y][t]))
		{
			ddprintf(this, "b == %u\n", b);
			
			unsigned s = t;
			
			while (!(true
				&& y < N(shifts) && b < N(*shifts)
				&& (d = shifts[y][b]) && (b != s)))
			{
				if (this->n == 1) return;
				
				s = this->data[--this->n - 1];
				y = this->data[--this->n - 1];
				
				ddprintf(this, "y == %u\n", y);
			}
			
			push(this, b), push(this, d), y = d;
			ddprintf(this, "y == %u\n", y);
		}
		else
		{
			assert(!"TODO");
			exit(1);
		}
	}
	
	push(this, t), push(this, b), y = b;
	ddprintf(this, "y == %u\n", y);
}

void zebu_parse(
	struct zebu_state* this,
	const unsigned char* text,
	size_t length)
{
	unsigned a, b, c, l = this->lstate;
	
	while (c = *text++, length--)
	{
		ddprintf(this, "c == %c\n", c);
		
		while (!(a = c < N(*lexer) ? lexer[l][c] : l < N(defaults) ? defaults[l] : 0))
		{
			if (l < N(accepts) && (b = accepts[l]))
			{
				process_token(this, b);
				
				l = starts[this->data[this->n - 1]];
				ddprintf(this, "l == %u\n", l);
			}
			else
			{
				assert(!"TODO");
				exit(1);
			}
		}
		
		l = a;
		ddprintf(this, "l == %u\n", l);
	}
	
	ddprintf(this, "l == %u\n", l);
	this->lstate = l;
}


void zebu_parse_EOF(
	struct zebu_state* this)
{
	unsigned b, l = this->lstate;
	
	ddprintf(this, "l == %u\n", l);
	
	if (l < N(accepts) && (b = accepts[l]))
	{
		process_token(this, b);
	}
	else
	{
		assert(!"TODO");
		exit(1);
	}
	
	process_token(this, 1);
}

void free_zebu_state(struct zebu_state* this)
{
	free(this->data);
	free(this);
}

static void check(const char* line, ...)
{
	struct zebu_state* state = new_zebu_state();
	
	{
		va_list va;
		
		va_start(va, line);
		
		printf("testing");
		const char* arg = line;
		do printf(" \"%s\"", arg);
		while ((arg = va_arg(va, char*)));
		
		puts("");
		
		va_end(va);
	}
	
	{
		va_list va;
		va_start(va, line);
		
		const char* arg = line;
		do zebu_parse(state, (void*) arg, strlen(line));
		while ((arg = va_arg(va, char*)));
		
		va_end(va);
	}
	
	zebu_parse_EOF(state);
	
	free_zebu_state(state);
	
	puts("accepts!");
}

int main()
{
	check("ABCCBA", NULL);
	
	check("ABC", "CBA", NULL);
	
	check("abc", NULL);
	
	check("abc::x!", NULL);
	
	check("a", "b", "c", ":", ":", "x", "!", NULL);
	
	check("bbaa", NULL);
	
	check("BaaB", "aBBa", NULL);
	
	check("abcc:x.", NULL);
	
	check("ABBABCCBCAAC", NULL);
	
	return 0;
}
















