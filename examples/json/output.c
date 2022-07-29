const unsigned zebu_shifts[19][13] = {
	[1][2] = 5,
	[1][3] = 4,
	[1][4] = 6,
	[1][5] = 3,
	[1][6] = 2,
	[1][7] = 7,
	[1][11] = 20,
	[6][2] = 5,
	[6][3] = 4,
	[6][4] = 6,
	[6][5] = 3,
	[6][6] = 2,
	[6][7] = 7,
	[6][11] = 16,
	[7][2] = 8,
	[8][12] = 9,
	[9][2] = 5,
	[9][3] = 4,
	[9][4] = 6,
	[9][5] = 3,
	[9][6] = 2,
	[9][7] = 7,
	[9][11] = 10,
	[10][8] = 11,
	[10][10] = 15,
	[11][2] = 12,
	[12][12] = 13,
	[13][2] = 5,
	[13][3] = 4,
	[13][4] = 6,
	[13][5] = 3,
	[13][6] = 2,
	[13][7] = 7,
	[13][11] = 14,
	[14][8] = 11,
	[14][10] = 15,
	[16][8] = 17,
	[16][9] = 19,
	[17][2] = 5,
	[17][3] = 4,
	[17][4] = 6,
	[17][5] = 3,
	[17][6] = 2,
	[17][7] = 7,
	[17][11] = 18,
	[18][8] = 17,
	[18][9] = 19,
};
const unsigned zebu_reduces[21][11] = {
	[2][1] = 11,
	[2][8] = 11,
	[2][9] = 11,
	[2][10] = 11,
	[3][1] = 11,
	[3][8] = 11,
	[3][9] = 11,
	[3][10] = 11,
	[4][1] = 11,
	[4][8] = 11,
	[4][9] = 11,
	[4][10] = 11,
	[5][1] = 11,
	[5][8] = 11,
	[5][9] = 11,
	[5][10] = 11,
	[15][1] = 11,
	[15][8] = 11,
	[15][9] = 11,
	[15][10] = 11,
	[19][1] = 11,
	[19][8] = 11,
	[19][9] = 11,
	[19][10] = 11,
	[20][1] = 13,
};
const unsigned zebu_lexer[31][126] = {
	[1][34] = 2,
	[1][48] = 5,
	[1][49] = 5,
	[1][50] = 5,
	[1][51] = 5,
	[1][52] = 5,
	[1][53] = 5,
	[1][54] = 5,
	[1][55] = 5,
	[1][56] = 5,
	[1][57] = 5,
	[1][91] = 6,
	[1][102] = 7,
	[1][116] = 12,
	[1][123] = 16,
	[2][97] = 3,
	[2][98] = 3,
	[2][99] = 3,
	[2][100] = 3,
	[2][101] = 3,
	[2][102] = 3,
	[2][103] = 3,
	[2][104] = 3,
	[2][105] = 3,
	[2][106] = 3,
	[2][107] = 3,
	[2][108] = 3,
	[2][109] = 3,
	[2][110] = 3,
	[2][111] = 3,
	[2][112] = 3,
	[2][113] = 3,
	[2][114] = 3,
	[2][115] = 3,
	[2][116] = 3,
	[2][117] = 3,
	[2][118] = 3,
	[2][119] = 3,
	[2][120] = 3,
	[2][121] = 3,
	[2][122] = 3,
	[3][34] = 4,
	[3][97] = 3,
	[3][98] = 3,
	[3][99] = 3,
	[3][100] = 3,
	[3][101] = 3,
	[3][102] = 3,
	[3][103] = 3,
	[3][104] = 3,
	[3][105] = 3,
	[3][106] = 3,
	[3][107] = 3,
	[3][108] = 3,
	[3][109] = 3,
	[3][110] = 3,
	[3][111] = 3,
	[3][112] = 3,
	[3][113] = 3,
	[3][114] = 3,
	[3][115] = 3,
	[3][116] = 3,
	[3][117] = 3,
	[3][118] = 3,
	[3][119] = 3,
	[3][120] = 3,
	[3][121] = 3,
	[3][122] = 3,
	[5][48] = 5,
	[5][49] = 5,
	[5][50] = 5,
	[5][51] = 5,
	[5][52] = 5,
	[5][53] = 5,
	[5][54] = 5,
	[5][55] = 5,
	[5][56] = 5,
	[5][57] = 5,
	[7][97] = 8,
	[8][108] = 9,
	[9][115] = 10,
	[10][101] = 11,
	[12][114] = 13,
	[13][117] = 14,
	[14][101] = 15,
	[17][44] = 18,
	[17][93] = 19,
	[17][125] = 20,
	[21][34] = 22,
	[22][97] = 23,
	[22][98] = 23,
	[22][99] = 23,
	[22][100] = 23,
	[22][101] = 23,
	[22][102] = 23,
	[22][103] = 23,
	[22][104] = 23,
	[22][105] = 23,
	[22][106] = 23,
	[22][107] = 23,
	[22][108] = 23,
	[22][109] = 23,
	[22][110] = 23,
	[22][111] = 23,
	[22][112] = 23,
	[22][113] = 23,
	[22][114] = 23,
	[22][115] = 23,
	[22][116] = 23,
	[22][117] = 23,
	[22][118] = 23,
	[22][119] = 23,
	[22][120] = 23,
	[22][121] = 23,
	[22][122] = 23,
	[23][34] = 24,
	[23][97] = 23,
	[23][98] = 23,
	[23][99] = 23,
	[23][100] = 23,
	[23][101] = 23,
	[23][102] = 23,
	[23][103] = 23,
	[23][104] = 23,
	[23][105] = 23,
	[23][106] = 23,
	[23][107] = 23,
	[23][108] = 23,
	[23][109] = 23,
	[23][110] = 23,
	[23][111] = 23,
	[23][112] = 23,
	[23][113] = 23,
	[23][114] = 23,
	[23][115] = 23,
	[23][116] = 23,
	[23][117] = 23,
	[23][118] = 23,
	[23][119] = 23,
	[23][120] = 23,
	[23][121] = 23,
	[23][122] = 23,
	[25][58] = 26,
	[27][44] = 28,
	[27][125] = 29,
	[30][44] = 31,
	[30][93] = 32,
};
const unsigned zebu_firsts[14][12] = {
	[11][2] = 1,
	[11][3] = 1,
	[11][4] = 1,
	[11][5] = 1,
	[11][6] = 1,
	[11][7] = 1,
	[13][2] = 1,
	[13][3] = 1,
	[13][4] = 1,
	[13][5] = 1,
	[13][6] = 1,
	[13][7] = 1,
	[13][11] = 1,
};
const unsigned zebu_starts[21] = {
	[1] = 1,
	[2] = 17,
	[3] = 17,
	[4] = 17,
	[5] = 17,
	[6] = 1,
	[7] = 21,
	[8] = 25,
	[9] = 1,
	[10] = 27,
	[11] = 21,
	[12] = 25,
	[13] = 1,
	[14] = 27,
	[15] = 17,
	[16] = 30,
	[17] = 1,
	[18] = 30,
	[19] = 17,
	[20] = 33,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_accepts[33] = {
	[4] = 2,
	[5] = 3,
	[6] = 4,
	[11] = 5,
	[15] = 6,
	[16] = 7,
	[18] = 8,
	[19] = 9,
	[20] = 10,
	[24] = 2,
	[26] = 12,
	[28] = 8,
	[29] = 10,
	[31] = 8,
	[32] = 9,
};
const char* zebu_grammar_names[15] = {
	[13] = "(start)",
	[11] = "value",
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
					case '[':
					case '{':
					case '}':
					case ',':
						case ']':
					case '(': case ')':
						*e++ = s;
						break;
					case '\n':
						*e++ = '\\';
						*e++ = 'n';
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
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
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
	unsigned i, n, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	
	for (i = this->l.n, n = i; ; )
	{
		assert(i <= n);
		
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
						case '!':
						case '[':
						case ']':
					case ',':
							*e++ = s;
							break;
						case '\n':
							*e++ = '\\';
							*e++ = 'n';
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
				ddprintf(this, "c == %u (%s)\n", c, escaped);
			}
			
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		}
		else
		{
			ddprintf(this, "c == <EOF>\n");
			a = 0;
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
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
			if (f >= n) break;
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
	
	process_token(this, 1);
}

void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
