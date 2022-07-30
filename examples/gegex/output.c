const unsigned zebu_shifts[9][12] = {
	[1][2] = 2,
	[1][3] = 5,
	[1][9] = 9,
	[2][4] = 6,
	[2][5] = 3,
	[2][10] = 8,
	[2][11] = 7,
	[3][6] = 4,
	[4][2] = 2,
	[4][3] = 5,
	[6][7] = 4,
	[7][6] = 4,
	[8][7] = 4,
};
const unsigned zebu_reduces[10][9] = {
	[3][7] = 10,
	[5][8] = 9,
	[6][6] = 11,
	[9][8] = 12,
};
const unsigned zebu_lexer[21][101] = {
	[1][44] = 2,
	[1][97] = 3,
	[1][100] = 4,
	[2][32] = 1,
	[5][44] = 6,
	[5][66] = 7,
	[5][98] = 8,
	[6][32] = 5,
	[9][44] = 10,
	[9][67] = 11,
	[9][99] = 12,
	[10][32] = 9,
	[13][44] = 14,
	[14][32] = 13,
	[16][44] = 17,
	[16][67] = 18,
	[17][32] = 16,
	[19][44] = 20,
	[19][99] = 21,
	[20][32] = 19,
};
const unsigned zebu_firsts[13][10] = {
	[9][2] = 1,
	[9][3] = 1,
	[10][5] = 1,
	[11][4] = 1,
	[12][2] = 1,
	[12][3] = 1,
	[12][9] = 1,
};
const unsigned zebu_starts[10] = {
	[1] = 1,
	[2] = 5,
	[3] = 9,
	[4] = 1,
	[5] = 13,
	[6] = 9,
	[7] = 16,
	[8] = 19,
	[9] = 13,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[14] = {
	[13] = 15,
};
const unsigned zebu_accepts[22] = {
	[3] = 2,
	[4] = 3,
	[7] = 4,
	[8] = 5,
	[11] = 6,
	[12] = 7,
	[15] = 8,
	[18] = 6,
	[21] = 7,
};
const char* zebu_grammar_names[14] = {
	[12] = "(start)",
	[11] = "B",
	[10] = "b",
	[9] = "gegex",
};
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct zebu_state
{
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};

static void push(struct zebu_state* this, unsigned ystate)
{
	if (this->y.n + 1 >= this->y.cap)
	{
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
	}
	
	this->y.data[this->y.n++] = ystate;
}

static void append(struct zebu_state* this, const unsigned char* text, size_t length)
{
	while (this->l.n + length >= this->l.cap)
	{
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	memcpy(this->l.data + this->l.n, text, length);
	this->l.n += length;
}

static void ddprintf(struct zebu_state* this, const char* fmt, ...)
{
	for (unsigned i = 0, n = this->y.n; i < n; i++)
	{
		printf("%u ", this->y.data[i]);
	}
	
	printf("| ");
	
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}

struct zebu_state* new_zebu_state() {
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}

void zebu_reset(struct zebu_state* this) {
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct zebu_state* this, unsigned t) {
	ddprintf(this, "t == %u\n", t);
	
	unsigned b, d, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t])))
	{
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t]))
		{
			ddprintf(this, "b == %u\n", b);
			ddprintf(this, "g == \"%s\"\n", zebu_grammar_names[b]);
			
			unsigned s = t;
			
			while (!(1
				 && y < N(zebu_shifts) && b < N(*zebu_shifts) && (d = zebu_shifts[y][b])
				 && b < N(zebu_firsts) && s < N(*zebu_firsts) && (    zebu_firsts[b][s])))
			{
				if (this->y.n == 1) return;
				s = this->y.data[--this->y.n - 1];
				y = this->y.data[--this->y.n - 1];
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
}

void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length) {
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	
	i = this->l.n;
	
	append(this, text, length);
	
	for (n = this->l.n, f = 0; i < n;)
	{
		c = this->l.data[i];
		
		{
			unsigned j, s;
			unsigned char escaped[(n - i) * 4 + 1], *e = escaped;
			for (j = i; j < n; j++)
				switch (s = this->l.data[j]) {
					case 'a' ... 'z':
					case 'A' ... 'Z':
					case '0' ... '9':
					case '!':
					case ':':
					case '.':
					case '+':
					case '%':
					case '[':
					case '{':
					case '-':
					case '}':
					case '*':
					case '|':
					case ',':
					case '@':
					case '<':
					case '>':
					case '&':
					case '~':
					case '^':
					case '/':
					case '?':
					case ' ':
					case ']':
					case '(': case ')':
					*e++ = s;
					break;
					case '\n':
						*e++ = '\\';
						*e++ = 'n';
					case '\\':
						*e++ = '\\';
						*e++ = '\\';
						break;
					case '\"':
						*e++ = '\\';
						*e++ = '"';
					break;
					default:
						printf("s = %c\n", s);
						assert(!"TODO");
						break;
				}
			*e = 0;
			ddprintf(this, "c == %u \"%s\"\n", c, escaped);
		}
		
		a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		
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
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
		}
		else if (t)
		{
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
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

void zebu_parse_EOF(struct zebu_state* this) {
	unsigned i = this->l.n, n = i, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	
	while (1)
	{
		assert(i <= n + 1);
		
		if (i < n)
		{
			c = this->l.data[i];
			
			{
				unsigned j, s;
				unsigned char escaped[(n - i) * 4 + 1], *e = escaped;
				for (j = i; j < n; j++)
					switch (s = this->l.data[j]) {
						case 'a' ... 'z':
						case 'A' ... 'Z':
						case '0' ... '9':
						case '+':
						case ':':
						case '.':
						case '{':
						case '}':
						case '%':
						case '!':
						case '~':
						case '[':
						case '*':
						case '>':
						case '^':
						case '?':
						case '/':
						case '|':
						case '<':
						case '@':
						case '-':
						case '&':
						case ']':
						case ',':
						case ' ':
							*e++ = s;
							break;
						case '\n':
							*e++ = '\\';
							*e++ = 'n';
						case '\"':
							*e++ = '\\';
							*e++ = '"';
						break;
					case '\\':
						*e++ = '\\';
						*e++ = '\\';
						break;
						default:
							printf("s = %c\n", s);
							assert(!"TODO");
							break;
					}
				*e = 0;
				ddprintf(this, "c == %u (%s)\n", c, escaped);
			}
			
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		}
		else
		{
			ddprintf(this, "c == <EOF>\n");
			a = l < N(zebu_EOFs) ? zebu_EOFs[l] : 0;
		}
		
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		
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
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
			if (f > n) break;
		}
		else if (t)
		{
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
		}
		else
		{
			assert(!"TODO");
		}
	}
}

void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
