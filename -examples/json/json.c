const unsigned zebu_shifts[53][16] = {
	[1][2] = 5,
	[1][3] = 4,
	[1][4] = 6,
	[1][5] = 3,
	[1][6] = 2,
	[1][7] = 48,
	[1][9] = 56,
	[6][2] = 10,
	[6][3] = 9,
	[6][4] = 11,
	[6][5] = 8,
	[6][6] = 7,
	[6][7] = 12,
	[6][9] = 44,
	[6][14] = 43,
	[11][2] = 10,
	[11][3] = 9,
	[11][4] = 11,
	[11][5] = 8,
	[11][6] = 7,
	[11][7] = 12,
	[11][9] = 39,
	[11][14] = 38,
	[12][2] = 13,
	[12][15] = 37,
	[13][12] = 14,
	[14][2] = 18,
	[14][3] = 17,
	[14][4] = 19,
	[14][5] = 16,
	[14][6] = 15,
	[14][7] = 25,
	[14][9] = 33,
	[19][2] = 10,
	[19][3] = 9,
	[19][4] = 11,
	[19][5] = 8,
	[19][6] = 7,
	[19][7] = 12,
	[19][9] = 21,
	[19][14] = 20,
	[21][10] = 22,
	[21][11] = 24,
	[22][2] = 10,
	[22][3] = 9,
	[22][4] = 11,
	[22][5] = 8,
	[22][6] = 7,
	[22][7] = 12,
	[22][9] = 21,
	[22][14] = 23,
	[25][2] = 26,
	[25][15] = 32,
	[26][12] = 27,
	[27][2] = 18,
	[27][3] = 17,
	[27][4] = 19,
	[27][5] = 16,
	[27][6] = 15,
	[27][7] = 25,
	[27][9] = 28,
	[28][10] = 29,
	[28][13] = 31,
	[29][2] = 26,
	[29][15] = 30,
	[33][10] = 34,
	[33][13] = 36,
	[34][2] = 13,
	[34][15] = 35,
	[39][10] = 40,
	[39][11] = 42,
	[40][2] = 10,
	[40][3] = 9,
	[40][4] = 11,
	[40][5] = 8,
	[40][6] = 7,
	[40][7] = 12,
	[40][9] = 39,
	[40][14] = 41,
	[44][10] = 45,
	[44][11] = 47,
	[45][2] = 10,
	[45][3] = 9,
	[45][4] = 11,
	[45][5] = 8,
	[45][6] = 7,
	[45][7] = 12,
	[45][9] = 44,
	[45][14] = 46,
	[48][2] = 49,
	[48][15] = 55,
	[49][12] = 50,
	[50][2] = 18,
	[50][3] = 17,
	[50][4] = 19,
	[50][5] = 16,
	[50][6] = 15,
	[50][7] = 25,
	[50][9] = 51,
	[51][10] = 52,
	[51][13] = 54,
	[52][2] = 49,
	[52][15] = 53,
};
const unsigned zebu_reduces[57][14] = {
	[2][8] = 9,
	[3][8] = 9,
	[4][8] = 9,
	[5][8] = 9,
	[7][10] = 9,
	[7][11] = 9,
	[8][10] = 9,
	[8][11] = 9,
	[9][10] = 9,
	[9][11] = 9,
	[10][10] = 9,
	[10][11] = 9,
	[15][10] = 9,
	[15][13] = 9,
	[16][10] = 9,
	[16][13] = 9,
	[17][10] = 9,
	[17][13] = 9,
	[18][10] = 9,
	[18][13] = 9,
	[20][10] = 9,
	[20][13] = 9,
	[23][10] = 14,
	[23][13] = 14,
	[24][10] = 14,
	[24][13] = 14,
	[30][10] = 15,
	[30][13] = 15,
	[31][10] = 15,
	[31][13] = 15,
	[32][10] = 9,
	[32][13] = 9,
	[35][10] = 15,
	[35][11] = 15,
	[36][10] = 15,
	[36][11] = 15,
	[37][10] = 9,
	[37][11] = 9,
	[38][10] = 9,
	[38][11] = 9,
	[41][10] = 14,
	[41][11] = 14,
	[42][10] = 14,
	[42][11] = 14,
	[43][8] = 9,
	[46][8] = 14,
	[47][8] = 14,
	[53][8] = 15,
	[54][8] = 15,
	[55][8] = 9,
	[56][8] = 16,
};
const unsigned zebu_popcounts[57][14] = {
	[2][8] = 1,
	[3][8] = 1,
	[4][8] = 1,
	[5][8] = 1,
	[7][10] = 1,
	[7][11] = 1,
	[8][10] = 1,
	[8][11] = 1,
	[9][10] = 1,
	[9][11] = 1,
	[10][10] = 1,
	[10][11] = 1,
	[15][10] = 1,
	[15][13] = 1,
	[16][10] = 1,
	[16][13] = 1,
	[17][10] = 1,
	[17][13] = 1,
	[18][10] = 1,
	[18][13] = 1,
	[20][10] = 2,
	[20][13] = 2,
	[23][10] = 3,
	[23][13] = 3,
	[24][10] = 2,
	[24][13] = 2,
	[30][10] = 5,
	[30][13] = 5,
	[31][10] = 4,
	[31][13] = 4,
	[32][10] = 2,
	[32][13] = 2,
	[35][10] = 5,
	[35][11] = 5,
	[36][10] = 4,
	[36][11] = 4,
	[37][10] = 2,
	[37][11] = 2,
	[38][10] = 2,
	[38][11] = 2,
	[41][10] = 3,
	[41][11] = 3,
	[42][10] = 2,
	[42][11] = 2,
	[43][8] = 2,
	[46][8] = 3,
	[47][8] = 2,
	[53][8] = 5,
	[54][8] = 4,
	[55][8] = 2,
	[56][8] = 1,
};
const unsigned zebu_lexer[26][126] = {
	[1][32] = 1,
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
	[17][32] = 17,
	[19][32] = 19,
	[19][44] = 20,
	[19][93] = 21,
	[22][32] = 22,
	[22][34] = 2,
	[23][32] = 23,
	[23][58] = 24,
	[25][32] = 25,
	[25][44] = 20,
	[25][125] = 26,
};
const unsigned zebu_starts[57] = {
	[1] = 1,
	[2] = 17,
	[3] = 17,
	[4] = 17,
	[5] = 17,
	[6] = 1,
	[7] = 19,
	[8] = 19,
	[9] = 19,
	[10] = 19,
	[11] = 1,
	[12] = 22,
	[13] = 23,
	[14] = 1,
	[15] = 25,
	[16] = 25,
	[17] = 25,
	[18] = 25,
	[19] = 1,
	[20] = 25,
	[21] = 19,
	[22] = 1,
	[23] = 25,
	[24] = 25,
	[25] = 22,
	[26] = 23,
	[27] = 1,
	[28] = 25,
	[29] = 22,
	[30] = 25,
	[31] = 25,
	[32] = 25,
	[33] = 25,
	[34] = 22,
	[35] = 19,
	[36] = 19,
	[37] = 19,
	[38] = 19,
	[39] = 19,
	[40] = 1,
	[41] = 19,
	[42] = 19,
	[43] = 17,
	[44] = 19,
	[45] = 1,
	[46] = 17,
	[47] = 17,
	[48] = 22,
	[49] = 23,
	[50] = 1,
	[51] = 25,
	[52] = 22,
	[53] = 17,
	[54] = 17,
	[55] = 17,
	[56] = 17,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[18] = {
	[17] = 18,
};
const unsigned zebu_accepts[27] = {
	[4] = 2,
	[5] = 3,
	[6] = 4,
	[11] = 5,
	[15] = 6,
	[16] = 7,
	[18] = 8,
	[20] = 10,
	[21] = 11,
	[24] = 12,
	[26] = 13,
};
const unsigned start_grammar_id = 16;
const char* zebu_grammar_names[18] = {
	[16] = "(start)",
	[14] = "(trie #1)",
	[15] = "(trie #2)",
	[9] = "value",
};

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

struct zebu_state
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

static struct zebu_state* new_zebu_state()
{
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}

static void zebu_reset(struct zebu_state* this)
{
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
	ddprintf(this, "y = %u, l == %u\n", 1, 1);
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct zebu_state* this, unsigned t)
{
	unsigned b, d, p, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t])))
	{
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t]))
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
			
			assert(y < N(zebu_shifts) && b < N(*zebu_shifts));
			
			d = zebu_shifts[y][b];
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
		case '-':
		case '+':
		case '=':
		case '|':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}

static void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length)
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
		
		a = (l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
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

static void zebu_parse_EOF(struct zebu_state* this)
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

static void free_zebu_state(struct zebu_state* this)
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










