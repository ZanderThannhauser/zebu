const unsigned zebu_shifts[51][27] = {
	[1][2] = 29,
	[1][3] = 27,
	[1][4] = 33,
	[1][5] = 11,
	[1][6] = 7,
	[1][7] = 14,
	[1][8] = 2,
	[1][9] = 15,
	[1][10] = 17,
	[1][11] = 19,
	[1][14] = 51,
	[1][20] = 41,
	[1][21] = 43,
	[1][22] = 45,
	[1][24] = 49,
	[1][25] = 48,
	[1][26] = 50,
	[2][12] = 4,
	[2][13] = 3,
	[4][12] = 4,
	[4][15] = 5,
	[5][16] = 6,
	[7][12] = 8,
	[8][17] = 9,
	[9][18] = 10,
	[11][12] = 12,
	[12][12] = 4,
	[12][15] = 5,
	[12][17] = 9,
	[12][19] = 13,
	[13][16] = 6,
	[13][18] = 10,
	[14][12] = 4,
	[15][9] = 16,
	[15][10] = 17,
	[15][11] = 19,
	[15][21] = 25,
	[15][22] = 26,
	[17][9] = 15,
	[17][10] = 18,
	[17][11] = 19,
	[17][20] = 23,
	[17][22] = 24,
	[19][9] = 15,
	[19][10] = 17,
	[19][11] = 20,
	[19][20] = 21,
	[19][21] = 22,
	[21][11] = 20,
	[22][11] = 20,
	[23][10] = 18,
	[24][10] = 18,
	[25][9] = 16,
	[26][9] = 16,
	[27][2] = 29,
	[27][3] = 28,
	[27][4] = 33,
	[27][9] = 15,
	[27][10] = 18,
	[27][11] = 19,
	[27][20] = 23,
	[27][22] = 24,
	[27][25] = 37,
	[27][26] = 38,
	[29][2] = 30,
	[29][4] = 33,
	[29][23] = 31,
	[29][24] = 39,
	[29][26] = 40,
	[31][2] = 29,
	[31][4] = 33,
	[31][23] = 32,
	[31][25] = 37,
	[31][26] = 38,
	[33][2] = 29,
	[33][4] = 34,
	[33][23] = 31,
	[33][24] = 36,
	[33][25] = 35,
	[35][4] = 34,
	[36][4] = 34,
	[37][23] = 32,
	[38][23] = 32,
	[39][2] = 30,
	[40][2] = 30,
	[41][11] = 19,
	[41][22] = 42,
	[42][9] = 15,
	[42][10] = 17,
	[42][11] = 19,
	[42][20] = 41,
	[42][21] = 43,
	[42][22] = 45,
	[43][9] = 15,
	[43][11] = 19,
	[43][20] = 44,
	[43][22] = 47,
	[44][9] = 15,
	[44][10] = 17,
	[44][11] = 19,
	[44][20] = 41,
	[44][21] = 43,
	[44][22] = 45,
	[45][9] = 15,
	[45][20] = 46,
	[46][9] = 15,
	[46][10] = 17,
	[46][11] = 19,
	[46][20] = 41,
	[46][21] = 43,
	[46][22] = 45,
	[47][9] = 15,
	[47][10] = 17,
	[47][11] = 19,
	[47][20] = 41,
	[47][21] = 43,
	[47][22] = 45,
	[48][2] = 29,
	[48][4] = 33,
	[48][23] = 31,
	[48][24] = 49,
	[48][25] = 48,
	[48][26] = 50,
	[49][2] = 29,
	[49][4] = 33,
	[49][23] = 31,
	[49][24] = 49,
	[49][25] = 48,
	[49][26] = 50,
	[50][2] = 29,
	[50][4] = 33,
	[50][23] = 31,
	[50][24] = 49,
	[50][25] = 48,
	[50][26] = 50,
};
const unsigned zebu_reduces[52][24] = {
	[2][1] = 14,
	[3][1] = 14,
	[6][1] = 14,
	[10][1] = 14,
	[16][1] = 20,
	[16][9] = 20,
	[16][10] = 20,
	[16][11] = 20,
	[18][9] = 21,
	[18][11] = 21,
	[20][1] = 22,
	[20][9] = 22,
	[20][10] = 22,
	[20][11] = 22,
	[28][1] = 24,
	[28][2] = 24,
	[28][4] = 24,
	[28][9] = 21,
	[28][11] = 21,
	[28][23] = 24,
	[30][1] = 25,
	[30][2] = 25,
	[30][4] = 25,
	[30][23] = 25,
	[32][1] = 24,
	[32][2] = 24,
	[32][4] = 24,
	[32][23] = 24,
	[34][1] = 26,
	[34][2] = 26,
	[34][4] = 26,
	[34][23] = 26,
	[42][1] = 14,
	[44][1] = 14,
	[46][1] = 14,
	[47][1] = 14,
	[48][1] = 14,
	[49][1] = 14,
	[50][1] = 14,
	[51][1] = 27,
};
const unsigned zebu_lexer[95][123] = {
	[1][65] = 2,
	[1][66] = 3,
	[1][67] = 4,
	[1][97] = 5,
	[1][98] = 26,
	[1][99] = 27,
	[5][97] = 6,
	[5][98] = 24,
	[6][97] = 7,
	[6][98] = 13,
	[7][97] = 8,
	[7][98] = 14,
	[8][97] = 9,
	[8][98] = 15,
	[9][97] = 10,
	[9][98] = 16,
	[10][97] = 11,
	[10][98] = 17,
	[11][97] = 6,
	[11][98] = 12,
	[12][98] = 13,
	[12][99] = 19,
	[13][98] = 14,
	[13][99] = 20,
	[14][98] = 15,
	[14][99] = 21,
	[15][98] = 16,
	[15][99] = 22,
	[16][98] = 17,
	[16][99] = 23,
	[17][98] = 12,
	[17][99] = 18,
	[18][99] = 19,
	[19][99] = 20,
	[20][99] = 21,
	[21][99] = 22,
	[22][99] = 23,
	[23][99] = 18,
	[24][98] = 13,
	[24][99] = 25,
	[25][99] = 20,
	[28][58] = 29,
	[28][63] = 30,
	[32][58] = 33,
	[32][120] = 34,
	[32][121] = 34,
	[32][122] = 34,
	[35][33] = 36,
	[37][58] = 38,
	[39][119] = 39,
	[39][120] = 39,
	[39][121] = 39,
	[41][46] = 42,
	[43][58] = 44,
	[43][119] = 45,
	[43][120] = 47,
	[43][121] = 47,
	[43][122] = 48,
	[45][119] = 45,
	[45][120] = 45,
	[45][121] = 45,
	[47][119] = 45,
	[47][120] = 45,
	[47][121] = 45,
	[49][33] = 50,
	[49][46] = 51,
	[52][66] = 53,
	[52][97] = 54,
	[52][98] = 53,
	[52][99] = 55,
	[56][66] = 57,
	[56][97] = 58,
	[56][98] = 57,
	[56][99] = 59,
	[60][97] = 61,
	[60][99] = 62,
	[63][99] = 64,
	[65][66] = 66,
	[65][98] = 66,
	[67][97] = 68,
	[69][65] = 70,
	[69][66] = 71,
	[69][67] = 72,
	[69][97] = 73,
	[69][98] = 74,
	[69][99] = 75,
	[76][65] = 77,
	[76][66] = 78,
	[76][67] = 79,
	[76][97] = 80,
	[76][99] = 81,
	[82][65] = 83,
	[82][66] = 84,
	[82][67] = 85,
	[86][65] = 87,
	[86][66] = 88,
	[86][67] = 89,
	[90][67] = 91,
	[92][66] = 93,
	[94][65] = 95,
};
const unsigned zebu_firsts[28][27] = {
	[14][2] = 1,
	[14][3] = 1,
	[14][4] = 1,
	[14][5] = 1,
	[14][6] = 1,
	[14][7] = 1,
	[14][8] = 1,
	[14][9] = 1,
	[14][10] = 1,
	[14][11] = 1,
	[14][20] = 1,
	[14][21] = 1,
	[14][22] = 1,
	[14][23] = 1,
	[14][24] = 1,
	[14][25] = 1,
	[14][26] = 1,
	[20][9] = 1,
	[21][3] = 1,
	[21][10] = 1,
	[22][11] = 1,
	[24][3] = 1,
	[24][23] = 1,
	[25][2] = 1,
	[26][4] = 1,
	[27][2] = 1,
	[27][3] = 1,
	[27][4] = 1,
	[27][5] = 1,
	[27][6] = 1,
	[27][7] = 1,
	[27][8] = 1,
	[27][9] = 1,
	[27][10] = 1,
	[27][11] = 1,
	[27][14] = 1,
	[27][23] = 1,
};
const unsigned zebu_starts[52] = {
	[1] = 1,
	[2] = 28,
	[3] = 31,
	[4] = 32,
	[5] = 35,
	[6] = 31,
	[7] = 37,
	[8] = 39,
	[9] = 41,
	[10] = 31,
	[11] = 37,
	[12] = 43,
	[13] = 49,
	[14] = 37,
	[15] = 52,
	[16] = 56,
	[17] = 52,
	[18] = 60,
	[19] = 52,
	[20] = 56,
	[21] = 63,
	[22] = 63,
	[23] = 65,
	[24] = 65,
	[25] = 67,
	[26] = 67,
	[27] = 69,
	[28] = 76,
	[29] = 82,
	[30] = 86,
	[31] = 82,
	[32] = 86,
	[33] = 82,
	[34] = 86,
	[35] = 90,
	[36] = 90,
	[37] = 92,
	[38] = 92,
	[39] = 94,
	[40] = 94,
	[41] = 63,
	[42] = 56,
	[43] = 60,
	[44] = 56,
	[45] = 67,
	[46] = 56,
	[47] = 56,
	[48] = 86,
	[49] = 86,
	[50] = 86,
	[51] = 31,
};
const unsigned zebu_defaults[48] = {
	[39] = 40,
	[43] = 46,
	[45] = 46,
	[47] = 46,
};
const unsigned zebu_accepts[96] = {
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 9,
	[18] = 6,
	[19] = 7,
	[20] = 6,
	[22] = 5,
	[25] = 8,
	[26] = 10,
	[27] = 11,
	[29] = 12,
	[30] = 13,
	[33] = 12,
	[34] = 15,
	[36] = 16,
	[38] = 12,
	[39] = 17,
	[42] = 18,
	[43] = 17,
	[44] = 12,
	[45] = 17,
	[47] = 19,
	[48] = 15,
	[50] = 16,
	[51] = 18,
	[53] = 10,
	[54] = 9,
	[55] = 11,
	[57] = 10,
	[58] = 9,
	[59] = 11,
	[61] = 9,
	[62] = 11,
	[64] = 11,
	[66] = 10,
	[68] = 9,
	[70] = 2,
	[71] = 3,
	[72] = 4,
	[73] = 9,
	[74] = 10,
	[75] = 11,
	[77] = 2,
	[78] = 23,
	[79] = 4,
	[80] = 9,
	[81] = 11,
	[83] = 2,
	[84] = 23,
	[85] = 4,
	[87] = 2,
	[88] = 23,
	[89] = 4,
	[91] = 4,
	[93] = 23,
	[95] = 2,
};
const char* zebu_grammar_names[29] = {
	[27] = "(start)",
	[20] = "0.a",
	[21] = "0.b",
	[22] = "0.c",
	[25] = "1.a",
	[24] = "1.b",
	[26] = "1.c",
	[14] = "start",
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
