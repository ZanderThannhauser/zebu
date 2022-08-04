const unsigned zebu_shifts[18][16] = {
	[1][2] = 3,
	[1][3] = 2,
	[1][10] = 5,
	[1][11] = 4,
	[1][12] = 19,
	[1][14] = 11,
	[3][2] = 3,
	[3][3] = 2,
	[3][10] = 5,
	[3][11] = 4,
	[3][12] = 17,
	[3][14] = 11,
	[5][5] = 6,
	[5][8] = 9,
	[6][2] = 3,
	[6][3] = 2,
	[6][10] = 5,
	[6][13] = 7,
	[6][14] = 8,
	[9][2] = 3,
	[9][3] = 2,
	[9][10] = 5,
	[9][13] = 10,
	[9][14] = 8,
	[11][6] = 12,
	[11][7] = 15,
	[12][2] = 3,
	[12][3] = 2,
	[12][10] = 5,
	[12][11] = 14,
	[12][14] = 11,
	[12][15] = 13,
	[15][2] = 3,
	[15][3] = 2,
	[15][10] = 5,
	[15][11] = 14,
	[15][14] = 11,
	[15][15] = 16,
	[17][4] = 18,
};
const unsigned zebu_reduces[20][10] = {
	[2][4] = 10,
	[2][5] = 10,
	[2][6] = 10,
	[2][7] = 10,
	[2][8] = 10,
	[2][9] = 10,
	[4][4] = 12,
	[4][9] = 12,
	[5][4] = 14,
	[5][6] = 14,
	[5][7] = 14,
	[5][9] = 14,
	[7][4] = 14,
	[7][6] = 14,
	[7][7] = 14,
	[7][9] = 14,
	[8][4] = 13,
	[8][6] = 13,
	[8][7] = 13,
	[8][9] = 13,
	[10][4] = 14,
	[10][6] = 14,
	[10][7] = 14,
	[10][9] = 14,
	[11][4] = 11,
	[11][9] = 11,
	[13][4] = 11,
	[13][9] = 11,
	[14][4] = 15,
	[14][9] = 15,
	[16][4] = 11,
	[16][9] = 11,
	[18][4] = 10,
	[18][5] = 10,
	[18][6] = 10,
	[18][7] = 10,
	[18][8] = 10,
	[18][9] = 10,
	[19][9] = 16,
};
const unsigned zebu_popcounts[20][10] = {
	[2][4] = 1,
	[2][5] = 1,
	[2][6] = 1,
	[2][7] = 1,
	[2][8] = 1,
	[2][9] = 1,
	[4][4] = 1,
	[4][9] = 1,
	[5][4] = 1,
	[5][6] = 1,
	[5][7] = 1,
	[5][9] = 1,
	[7][4] = 3,
	[7][6] = 3,
	[7][7] = 3,
	[7][9] = 3,
	[8][4] = 1,
	[8][6] = 1,
	[8][7] = 1,
	[8][9] = 1,
	[10][4] = 3,
	[10][6] = 3,
	[10][7] = 3,
	[10][9] = 3,
	[11][4] = 1,
	[11][9] = 1,
	[13][4] = 3,
	[13][9] = 3,
	[14][4] = 1,
	[14][9] = 1,
	[16][4] = 3,
	[16][9] = 3,
	[18][4] = 3,
	[18][5] = 3,
	[18][6] = 3,
	[18][7] = 3,
	[18][8] = 3,
	[18][9] = 3,
	[19][9] = 1,
};
const unsigned zebu_lexer[22][58] = {
	[1][32] = 1,
	[1][40] = 2,
	[1][48] = 3,
	[1][49] = 3,
	[1][50] = 3,
	[1][51] = 3,
	[1][52] = 3,
	[1][53] = 3,
	[1][54] = 3,
	[1][55] = 3,
	[1][56] = 3,
	[1][57] = 3,
	[3][48] = 3,
	[3][49] = 3,
	[3][50] = 3,
	[3][51] = 3,
	[3][52] = 3,
	[3][53] = 3,
	[3][54] = 3,
	[3][55] = 3,
	[3][56] = 3,
	[3][57] = 3,
	[4][32] = 4,
	[4][41] = 5,
	[4][42] = 6,
	[4][43] = 7,
	[4][45] = 8,
	[4][47] = 9,
	[11][32] = 11,
	[11][41] = 12,
	[14][32] = 14,
	[14][41] = 15,
	[14][43] = 16,
	[14][45] = 17,
	[19][32] = 19,
	[19][41] = 20,
	[21][32] = 21,
};
const unsigned zebu_starts[20] = {
	[1] = 1,
	[2] = 4,
	[3] = 1,
	[4] = 11,
	[5] = 4,
	[6] = 1,
	[7] = 14,
	[8] = 14,
	[9] = 1,
	[10] = 14,
	[11] = 14,
	[12] = 1,
	[13] = 11,
	[14] = 11,
	[15] = 1,
	[16] = 11,
	[17] = 19,
	[18] = 4,
	[19] = 21,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[22] = {
	[4] = 10,
	[11] = 13,
	[14] = 18,
	[21] = 22,
};
const unsigned zebu_accepts[23] = {
	[2] = 2,
	[3] = 3,
	[5] = 4,
	[6] = 5,
	[7] = 6,
	[8] = 7,
	[9] = 8,
	[10] = 9,
	[12] = 4,
	[13] = 9,
	[15] = 4,
	[16] = 6,
	[17] = 7,
	[18] = 9,
	[20] = 4,
	[22] = 9,
};
const unsigned start_grammar_id = 16;
const char* zebu_grammar_names[18] = {
	[16] = "(start)",
	[13] = "(trie #1)",
	[15] = "(trie #2)",
	[11] = "add",
	[10] = "lit",
	[14] = "mul",
	[12] = "root",
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
	
	unsigned b, d, p, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t])))
	{
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t]))
		{
			ddprintf(this, "b == %u\n", b);
			ddprintf(this, "g == \"%s\"\n", zebu_grammar_names[b]);
			ddprintf(this, "p == %u\n", p = zebu_popcounts[y][t]);
			
			if (b == start_grammar_id)
			{
				this->y.n = 0;
				ddprintf(this, "done\n");
				return;
			}
			
			this->y.n -= p;
			
			y = this->y.data[this->y.n - 1];
			ddprintf(this, "y == %u\n", y);
			
			assert(y < N(zebu_shifts) && b < N(*zebu_shifts));
			
			d = zebu_shifts[y][b];
			
			push(this, d), y = d;
			ddprintf(this, "y == %u\n", y); 
		}
		else
		{
			assert(!"TODO");
			exit(1);
		}
	}
	
	push(this, b), y = b;
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
			if (!this->y.n) break;
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
}

void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
