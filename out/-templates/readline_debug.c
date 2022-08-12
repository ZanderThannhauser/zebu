
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct <PREFIX>_state
{
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};

static void ddprintf(struct zebu_state* this, const char* fmt, ...)
{
	for (unsigned i = 0, n = this->y.n; i < n; i++)
		printf("%u ", this->y.data[i]);
	
	printf("| ");
	
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}

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

static struct <PREFIX>_state* new_<PREFIX>_state()
{
	struct <PREFIX>_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}

static void <PREFIX>_reset(struct <PREFIX>_state* this)
{
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
	ddprintf(this, "y = %u, l == %u\n", 1, 1);
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct <PREFIX>_state* this, unsigned t)
{
	unsigned b, d, p, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(<PREFIX>_shifts) && t < N(*<PREFIX>_shifts) && (b = <PREFIX>_shifts[y][t])))
	{
		if (y < N(<PREFIX>_reduces) && t < N(*<PREFIX>_reduces) && (b = <PREFIX>_reduces[y][t]))
		{
			ddprintf(this, "b == %u\n", b);
			ddprintf(this, "g == \"%s\"\n", zebu_grammar_names[b]);
			
			if (b == start_grammar_id)
			{
				this->y.n = 0;
				return;
			}
			
			ddprintf(this, "p == %u\n", p = zebu_popcounts[y][t]);
			
			this->y.n -= p;
			
			y = this->y.data[this->y.n - 1];
			ddprintf(this, "y = %u\n", y);
			
			assert(y < N(<PREFIX>_shifts) && b < N(*<PREFIX>_shifts));
			
			d = <PREFIX>_shifts[y][b];
			ddprintf(this, "d = %u\n", d);
			
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
		case '(':
		case ')':
		case '-':
		case '+':
		case '=':
		case '|':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}

static void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length)
{
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	
	char escaped[10];
	
	i = this->l.n;
	
	append(this, text, length);
	
	for (n = this->l.n, f = 0; i < n;)
	{
		c = this->l.data[i];
		
		escape(escaped, c);
		
		ddprintf(this, "c = %s (0x%X)\n", escaped, c);
		
		a = (l < N(<PREFIX>_lexer) && c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);
		b = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);
		
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
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
		}
		else if (t)
		{
			process_token(this, t);
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
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
	
	char escaped[10];
	
	while (1)
	{
		assert(i <= n + 1);
		
		if (i < n)
		{
			c = this->l.data[i];
			
			escape(escaped, c);
			
			ddprintf(this, "c = %s (0x%X)\n", escaped, c);
		
			a = (c < N(*<PREFIX>_lexer) ? <PREFIX>_lexer[l][c] : 0) ?: (l < N( <PREFIX>_defaults) ? <PREFIX>_defaults[l] : 0);
		}
		else
		{
			ddprintf(this, "c == <EOF>\n");
			a = l < N(<PREFIX>_EOFs) ? <PREFIX>_EOFs[l] : 0;
		}
		
		b = (l < N(<PREFIX>_accepts) ? <PREFIX>_accepts[l] : 0);
		
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
			
			if (!this->y.n) break;
			
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
		}
		else if (t)
		{
			process_token(this, t);
			l = <PREFIX>_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
		}
		else
		{
			assert(!"TODO");
		}
	}
}

static void free_<PREFIX>_state(struct <PREFIX>_state* this)
{
	free(this->y.data);
	free(this->l.data);
	free(this);
}

int main()
{
	struct zebu_state* new = new_zebu_state();
	
	for (char* line; (line = readline(">>> "));)
	{
		zebu_reset(new);
		
		zebu_parse(new, (unsigned char*) line, strlen(line));
		
		zebu_parse_EOF(new);
		
		puts("accepted!");
		
		add_history(line);
		
		free(line);
	}
	
	free_zebu_state(new);
	
	return 0;
}










