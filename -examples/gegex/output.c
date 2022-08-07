const unsigned zebu_shifts[23][14] = {
	[1][2] = 2,
	[1][8] = 25,
	[2][3] = 7,
	[2][4] = 3,
	[2][11] = 12,
	[2][12] = 10,
	[3][5] = 4,
	[3][10] = 6,
	[4][2] = 2,
	[4][8] = 5,
	[7][6] = 8,
	[8][2] = 2,
	[8][8] = 9,
	[10][5] = 4,
	[10][10] = 11,
	[12][2] = 13,
	[12][6] = 22,
	[12][7] = 24,
	[13][4] = 14,
	[13][13] = 21,
	[14][2] = 15,
	[15][4] = 16,
	[15][11] = 17,
	[17][2] = 18,
	[17][7] = 20,
	[18][4] = 14,
	[18][13] = 19,
	[22][2] = 2,
	[22][8] = 23,
};
const unsigned zebu_reduces[26][10] = {
	[3][2] = 11,
	[3][6] = 11,
	[3][7] = 11,
	[5][9] = 10,
	[6][9] = 8,
	[7][5] = 12,
	[9][9] = 8,
	[11][9] = 8,
	[16][2] = 11,
	[16][6] = 11,
	[16][7] = 11,
	[19][9] = 13,
	[20][9] = 13,
	[21][9] = 8,
	[23][9] = 8,
	[24][9] = 8,
	[25][9] = 14,
};
const unsigned zebu_popcounts[26][10] = {
	[3][2] = 1,
	[3][6] = 1,
	[3][7] = 1,
	[5][9] = 2,
	[6][9] = 3,
	[7][5] = 1,
	[9][9] = 4,
	[11][9] = 3,
	[16][2] = 1,
	[16][6] = 1,
	[16][7] = 1,
	[19][9] = 5,
	[20][9] = 4,
	[21][9] = 4,
	[23][9] = 4,
	[24][9] = 3,
	[25][9] = 1,
};
const unsigned zebu_lexer[34][101] = {
	[1][44] = 2,
	[1][97] = 3,
	[2][32] = 1,
	[4][44] = 5,
	[4][66] = 6,
	[4][98] = 7,
	[5][32] = 4,
	[8][44] = 9,
	[8][67] = 10,
	[8][97] = 11,
	[8][99] = 12,
	[8][100] = 13,
	[9][32] = 8,
	[14][44] = 15,
	[15][32] = 14,
	[17][44] = 18,
	[17][67] = 19,
	[17][99] = 20,
	[18][32] = 17,
	[21][44] = 22,
	[21][67] = 23,
	[22][32] = 21,
	[24][44] = 25,
	[24][97] = 26,
	[24][99] = 27,
	[24][100] = 28,
	[25][32] = 24,
	[29][44] = 30,
	[29][98] = 31,
	[30][32] = 29,
	[32][44] = 33,
	[32][97] = 34,
	[32][100] = 35,
	[33][32] = 32,
};
const unsigned zebu_starts[26] = {
	[1] = 1,
	[2] = 4,
	[3] = 8,
	[4] = 1,
	[5] = 14,
	[6] = 14,
	[7] = 17,
	[8] = 1,
	[9] = 14,
	[10] = 21,
	[11] = 14,
	[12] = 24,
	[13] = 29,
	[14] = 1,
	[15] = 29,
	[16] = 24,
	[17] = 32,
	[18] = 29,
	[19] = 14,
	[20] = 14,
	[21] = 14,
	[22] = 1,
	[23] = 14,
	[24] = 14,
	[25] = 14,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[15] = {
	[14] = 16,
};
const unsigned zebu_accepts[36] = {
	[3] = 2,
	[6] = 3,
	[7] = 4,
	[10] = 5,
	[11] = 2,
	[12] = 6,
	[13] = 7,
	[16] = 9,
	[19] = 5,
	[20] = 6,
	[23] = 5,
	[26] = 2,
	[27] = 6,
	[28] = 7,
	[31] = 4,
	[34] = 2,
	[35] = 7,
};
const unsigned start_grammar_id = 14;
const char* zebu_grammar_names[16] = {
	[14] = "(start)",
	[10] = "(trie #0)",
	[13] = "(trie #1)",
	[12] = "B",
	[11] = "b",
	[8] = "gegex",
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








