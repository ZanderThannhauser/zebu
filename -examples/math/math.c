const unsigned zebu_shifts[35][16] = {
	[1][2] = 3,
	[1][3] = 2,
	[1][9] = 24,
	[1][11] = 23,
	[1][12] = 36,
	[1][14] = 30,
	[3][2] = 5,
	[3][3] = 4,
	[3][9] = 7,
	[3][11] = 6,
	[3][12] = 21,
	[3][14] = 13,
	[5][2] = 5,
	[5][3] = 4,
	[5][9] = 7,
	[5][11] = 6,
	[5][12] = 19,
	[5][14] = 13,
	[7][4] = 8,
	[7][7] = 11,
	[8][2] = 5,
	[8][3] = 4,
	[8][9] = 7,
	[8][13] = 9,
	[8][14] = 10,
	[11][2] = 5,
	[11][3] = 4,
	[11][9] = 7,
	[11][13] = 12,
	[11][14] = 10,
	[13][5] = 14,
	[13][6] = 17,
	[14][2] = 5,
	[14][3] = 4,
	[14][9] = 7,
	[14][11] = 16,
	[14][14] = 13,
	[14][15] = 15,
	[17][2] = 5,
	[17][3] = 4,
	[17][9] = 7,
	[17][11] = 16,
	[17][14] = 13,
	[17][15] = 18,
	[19][10] = 20,
	[21][10] = 22,
	[24][4] = 25,
	[24][7] = 28,
	[25][2] = 3,
	[25][3] = 2,
	[25][9] = 24,
	[25][13] = 26,
	[25][14] = 27,
	[28][2] = 3,
	[28][3] = 2,
	[28][9] = 24,
	[28][13] = 29,
	[28][14] = 27,
	[30][5] = 31,
	[30][6] = 34,
	[31][2] = 3,
	[31][3] = 2,
	[31][9] = 24,
	[31][11] = 33,
	[31][14] = 30,
	[31][15] = 32,
	[34][2] = 3,
	[34][3] = 2,
	[34][9] = 24,
	[34][11] = 33,
	[34][14] = 30,
	[34][15] = 35,
};
const unsigned zebu_reduces[37][11] = {
	[2][4] = 9,
	[2][5] = 9,
	[2][6] = 9,
	[2][7] = 9,
	[2][8] = 9,
	[4][4] = 9,
	[4][5] = 9,
	[4][6] = 9,
	[4][7] = 9,
	[4][10] = 9,
	[6][10] = 12,
	[7][5] = 14,
	[7][6] = 14,
	[7][10] = 14,
	[9][5] = 14,
	[9][6] = 14,
	[9][10] = 14,
	[10][5] = 13,
	[10][6] = 13,
	[10][10] = 13,
	[12][5] = 14,
	[12][6] = 14,
	[12][10] = 14,
	[13][10] = 11,
	[15][10] = 11,
	[16][10] = 15,
	[18][10] = 11,
	[20][4] = 9,
	[20][5] = 9,
	[20][6] = 9,
	[20][7] = 9,
	[20][10] = 9,
	[22][4] = 9,
	[22][5] = 9,
	[22][6] = 9,
	[22][7] = 9,
	[22][8] = 9,
	[23][8] = 12,
	[24][5] = 14,
	[24][6] = 14,
	[24][8] = 14,
	[26][5] = 14,
	[26][6] = 14,
	[26][8] = 14,
	[27][5] = 13,
	[27][6] = 13,
	[27][8] = 13,
	[29][5] = 14,
	[29][6] = 14,
	[29][8] = 14,
	[30][8] = 11,
	[32][8] = 11,
	[33][8] = 15,
	[35][8] = 11,
	[36][8] = 16,
};
const unsigned zebu_popcounts[37][11] = {
	[2][4] = 1,
	[2][5] = 1,
	[2][6] = 1,
	[2][7] = 1,
	[2][8] = 1,
	[4][4] = 1,
	[4][5] = 1,
	[4][6] = 1,
	[4][7] = 1,
	[4][10] = 1,
	[6][10] = 1,
	[7][5] = 1,
	[7][6] = 1,
	[7][10] = 1,
	[9][5] = 3,
	[9][6] = 3,
	[9][10] = 3,
	[10][5] = 1,
	[10][6] = 1,
	[10][10] = 1,
	[12][5] = 3,
	[12][6] = 3,
	[12][10] = 3,
	[13][10] = 1,
	[15][10] = 3,
	[16][10] = 1,
	[18][10] = 3,
	[20][4] = 3,
	[20][5] = 3,
	[20][6] = 3,
	[20][7] = 3,
	[20][10] = 3,
	[22][4] = 3,
	[22][5] = 3,
	[22][6] = 3,
	[22][7] = 3,
	[22][8] = 3,
	[23][8] = 1,
	[24][5] = 1,
	[24][6] = 1,
	[24][8] = 1,
	[26][5] = 3,
	[26][6] = 3,
	[26][8] = 3,
	[27][5] = 1,
	[27][6] = 1,
	[27][8] = 1,
	[29][5] = 3,
	[29][6] = 3,
	[29][8] = 3,
	[30][8] = 1,
	[32][8] = 3,
	[33][8] = 1,
	[35][8] = 3,
	[36][8] = 1,
};
const unsigned zebu_lexer[25][58] = {
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
	[4][42] = 5,
	[4][43] = 6,
	[4][45] = 7,
	[4][47] = 8,
	[10][32] = 10,
	[10][41] = 11,
	[10][42] = 12,
	[10][43] = 13,
	[10][45] = 14,
	[10][47] = 15,
	[16][32] = 16,
	[16][41] = 17,
	[18][32] = 18,
	[18][41] = 19,
	[18][43] = 20,
	[18][45] = 21,
	[22][32] = 22,
	[24][32] = 24,
	[24][43] = 25,
	[24][45] = 26,
};
const unsigned zebu_starts[37] = {
	[1] = 1,
	[2] = 4,
	[3] = 1,
	[4] = 10,
	[5] = 1,
	[6] = 16,
	[7] = 10,
	[8] = 1,
	[9] = 18,
	[10] = 18,
	[11] = 1,
	[12] = 18,
	[13] = 18,
	[14] = 1,
	[15] = 16,
	[16] = 16,
	[17] = 1,
	[18] = 16,
	[19] = 16,
	[20] = 10,
	[21] = 16,
	[22] = 4,
	[23] = 22,
	[24] = 4,
	[25] = 1,
	[26] = 24,
	[27] = 24,
	[28] = 1,
	[29] = 24,
	[30] = 24,
	[31] = 1,
	[32] = 22,
	[33] = 22,
	[34] = 1,
	[35] = 22,
	[36] = 22,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[25] = {
	[4] = 9,
	[22] = 23,
	[24] = 27,
};
const unsigned zebu_accepts[28] = {
	[2] = 2,
	[3] = 3,
	[5] = 4,
	[6] = 5,
	[7] = 6,
	[8] = 7,
	[9] = 8,
	[11] = 10,
	[12] = 4,
	[13] = 5,
	[14] = 6,
	[15] = 7,
	[17] = 10,
	[19] = 10,
	[20] = 5,
	[21] = 6,
	[23] = 8,
	[25] = 5,
	[26] = 6,
	[27] = 8,
};
const unsigned start_grammar_id = 16;
const char* zebu_grammar_names[18] = {
	[16] = "(start)",
	[13] = "(trie #1)",
	[15] = "(trie #2)",
	[11] = "add",
	[9] = "lit",
	[14] = "mul",
	[12] = "root",
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










