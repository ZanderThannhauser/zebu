
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

struct <PREFIX>_state
{
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};

static void push(struct <PREFIX>_state* this, unsigned ystate)
{
	if (this->y.n + 1 >= this->y.cap)
	{
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
	}
	
	this->y.data[this->y.n++] = ystate;
}

static void append(struct <PREFIX>_state* this, const unsigned char* text, size_t length)
{
	while (this->l.n + length >= this->l.cap)
	{
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	memcpy(this->l.data + this->l.n, text, length);
	this->l.n += length;
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct <PREFIX>_state* this, unsigned t)
{
	unsigned b, d, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (b = <PREFIX>_shifts[y][t])))
	{
		if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (b = <PREFIX>_reduces[y][t]))
		{
			if (b == start_grammar_id)
			{
				this->y.n = 0;
				return;
			}
			
			this->y.n -= <PREFIX>_popcounts[y][t];
			
			y = this->y.data[this->y.n - 1];
			
			assert(y < N(<PREFIX>_shifts) && b < N(*<PREFIX>_shifts));
			
			d = <PREFIX>_shifts[y][b];
			
			push(this, d), y = d;
		}
		else
		{
			assert(!"TODO");
			exit(1);
		}
	}
	
	push(this, b), y = b;
}

static void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length)
{
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	
	i = this->l.n;
	
	append(this, text, length);
	
	for (n = this->l.n, f = 0; i < n;)
	{
		c = this->l.data[i];
		
		a = (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);
		b = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
			}
			else
			{
				l = a, i++;
			}
		}
		else if (b)
		{
			process_token(this, b);
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
		}
		else if (t)
		{
			process_token(this, t);
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		}
		else
		{
			assert(!"TODO");
		}
	}
	
	memcpy(this->l.data, this->l.data + f, this->l.n = n - f);
	
	this->t = t;
	
	this->lstate = l;
}

static void <PREFIX>_parse_EOF(struct <PREFIX>_state* this)
{
	unsigned i = this->l.n, n = i, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	
	while (1)
	{
		assert(i <= n + 1);
		
		if (i < n)
		{
			c = this->l.data[i];
			
			a = (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);
		}
		else
		{
			a = l < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[l] : 0;
		}
		
		b = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
			}
			else
			{
				l = a, i++;
			}
		}
		else if (b)
		{
			process_token(this, b);
			
			if (!this->y.n) break;
			
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
		}
		else if (t)
		{
			process_token(this, t);
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		}
		else
		{
			assert(!"TODO");
		}
	}
}

int main()
{
	struct <PREFIX>_state this = {};
	
	this->lstate = 1, this->t = 0;
	
	push(this, 1);
	
	for (char* line; (line = readline(">>> "));)
	{
		this->y.n = 0;
		this->l.n = 0;
		this->lstate = 1;
		push(this, 1);
		
		zebu_parse(new, (unsigned char*) line, strlen(line));
		
		zebu_parse_EOF(new);
		
		puts("accepted!");
		
		add_history(line);
		
		free(line);
	}
	
	free(this.y.data);
	free(this.l.data);
	free(this);
	
	return 0;
}










