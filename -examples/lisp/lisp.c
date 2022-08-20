const unsigned zebu_shifts[20][10] = {
	[1][2] = 5,
	[1][3] = 2,
	[1][4] = 3,
	[1][5] = 4,
	[1][7] = 22,
	[4][2] = 5,
	[4][3] = 2,
	[4][4] = 3,
	[4][5] = 4,
	[4][7] = 21,
	[5][2] = 9,
	[5][3] = 6,
	[5][4] = 7,
	[5][5] = 8,
	[5][7] = 16,
	[8][2] = 9,
	[8][3] = 6,
	[8][4] = 7,
	[8][5] = 8,
	[8][7] = 15,
	[9][2] = 9,
	[9][3] = 6,
	[9][4] = 7,
	[9][5] = 8,
	[9][7] = 10,
	[10][2] = 9,
	[10][3] = 6,
	[10][4] = 7,
	[10][5] = 8,
	[10][7] = 13,
	[10][8] = 11,
	[10][9] = 12,
	[13][2] = 9,
	[13][3] = 6,
	[13][4] = 7,
	[13][5] = 8,
	[13][7] = 13,
	[13][8] = 11,
	[13][9] = 14,
	[16][2] = 9,
	[16][3] = 6,
	[16][4] = 7,
	[16][5] = 8,
	[16][7] = 19,
	[16][8] = 17,
	[16][9] = 18,
	[19][2] = 9,
	[19][3] = 6,
	[19][4] = 7,
	[19][5] = 8,
	[19][7] = 19,
	[19][8] = 17,
	[19][9] = 20,
};
const unsigned zebu_reduces[23][9] = {
	[2][6] = 7,
	[3][6] = 7,
	[6][2] = 7,
	[6][3] = 7,
	[6][4] = 7,
	[6][5] = 7,
	[6][8] = 7,
	[7][2] = 7,
	[7][3] = 7,
	[7][4] = 7,
	[7][5] = 7,
	[7][8] = 7,
	[11][2] = 9,
	[11][3] = 9,
	[11][4] = 9,
	[11][5] = 9,
	[11][8] = 9,
	[12][2] = 7,
	[12][3] = 7,
	[12][4] = 7,
	[12][5] = 7,
	[12][8] = 7,
	[14][2] = 9,
	[14][3] = 9,
	[14][4] = 9,
	[14][5] = 9,
	[14][8] = 9,
	[15][2] = 7,
	[15][3] = 7,
	[15][4] = 7,
	[15][5] = 7,
	[15][8] = 7,
	[17][6] = 9,
	[18][6] = 7,
	[20][6] = 9,
	[21][6] = 7,
	[22][6] = 10,
};
const unsigned zebu_popcounts[23][9] = {
	[2][6] = 1,
	[3][6] = 1,
	[6][2] = 1,
	[6][3] = 1,
	[6][4] = 1,
	[6][5] = 1,
	[6][8] = 1,
	[7][2] = 1,
	[7][3] = 1,
	[7][4] = 1,
	[7][5] = 1,
	[7][8] = 1,
	[11][2] = 1,
	[11][3] = 1,
	[11][4] = 1,
	[11][5] = 1,
	[11][8] = 1,
	[12][2] = 3,
	[12][3] = 3,
	[12][4] = 3,
	[12][5] = 3,
	[12][8] = 3,
	[14][2] = 2,
	[14][3] = 2,
	[14][4] = 2,
	[14][5] = 2,
	[14][8] = 2,
	[15][2] = 2,
	[15][3] = 2,
	[15][4] = 2,
	[15][5] = 2,
	[15][8] = 2,
	[17][6] = 1,
	[18][6] = 3,
	[20][6] = 2,
	[21][6] = 2,
	[22][6] = 1,
};
const unsigned zebu_lexer[13][123] = {
	[1][9] = 1,
	[1][10] = 1,
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
	[1][65] = 4,
	[1][66] = 4,
	[1][67] = 4,
	[1][68] = 4,
	[1][69] = 4,
	[1][70] = 4,
	[1][71] = 4,
	[1][72] = 4,
	[1][73] = 4,
	[1][74] = 4,
	[1][75] = 4,
	[1][76] = 4,
	[1][77] = 4,
	[1][78] = 4,
	[1][79] = 4,
	[1][80] = 4,
	[1][81] = 4,
	[1][82] = 4,
	[1][83] = 4,
	[1][84] = 4,
	[1][85] = 4,
	[1][86] = 4,
	[1][87] = 4,
	[1][88] = 4,
	[1][89] = 4,
	[1][90] = 4,
	[1][96] = 5,
	[1][97] = 4,
	[1][98] = 4,
	[1][99] = 4,
	[1][100] = 4,
	[1][101] = 4,
	[1][102] = 4,
	[1][103] = 4,
	[1][104] = 4,
	[1][105] = 4,
	[1][106] = 4,
	[1][107] = 4,
	[1][108] = 4,
	[1][109] = 4,
	[1][110] = 4,
	[1][111] = 4,
	[1][112] = 4,
	[1][113] = 4,
	[1][114] = 4,
	[1][115] = 4,
	[1][116] = 4,
	[1][117] = 4,
	[1][118] = 4,
	[1][119] = 4,
	[1][120] = 4,
	[1][121] = 4,
	[1][122] = 4,
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
	[4][65] = 4,
	[4][66] = 4,
	[4][67] = 4,
	[4][68] = 4,
	[4][69] = 4,
	[4][70] = 4,
	[4][71] = 4,
	[4][72] = 4,
	[4][73] = 4,
	[4][74] = 4,
	[4][75] = 4,
	[4][76] = 4,
	[4][77] = 4,
	[4][78] = 4,
	[4][79] = 4,
	[4][80] = 4,
	[4][81] = 4,
	[4][82] = 4,
	[4][83] = 4,
	[4][84] = 4,
	[4][85] = 4,
	[4][86] = 4,
	[4][87] = 4,
	[4][88] = 4,
	[4][89] = 4,
	[4][90] = 4,
	[4][97] = 4,
	[4][98] = 4,
	[4][99] = 4,
	[4][100] = 4,
	[4][101] = 4,
	[4][102] = 4,
	[4][103] = 4,
	[4][104] = 4,
	[4][105] = 4,
	[4][106] = 4,
	[4][107] = 4,
	[4][108] = 4,
	[4][109] = 4,
	[4][110] = 4,
	[4][111] = 4,
	[4][112] = 4,
	[4][113] = 4,
	[4][114] = 4,
	[4][115] = 4,
	[4][116] = 4,
	[4][117] = 4,
	[4][118] = 4,
	[4][119] = 4,
	[4][120] = 4,
	[4][121] = 4,
	[4][122] = 4,
	[6][9] = 6,
	[6][10] = 6,
	[6][32] = 6,
	[8][9] = 8,
	[8][10] = 8,
	[8][32] = 8,
	[8][40] = 9,
	[8][41] = 10,
	[8][48] = 11,
	[8][49] = 11,
	[8][50] = 11,
	[8][51] = 11,
	[8][52] = 11,
	[8][53] = 11,
	[8][54] = 11,
	[8][55] = 11,
	[8][56] = 11,
	[8][57] = 11,
	[8][65] = 12,
	[8][66] = 12,
	[8][67] = 12,
	[8][68] = 12,
	[8][69] = 12,
	[8][70] = 12,
	[8][71] = 12,
	[8][72] = 12,
	[8][73] = 12,
	[8][74] = 12,
	[8][75] = 12,
	[8][76] = 12,
	[8][77] = 12,
	[8][78] = 12,
	[8][79] = 12,
	[8][80] = 12,
	[8][81] = 12,
	[8][82] = 12,
	[8][83] = 12,
	[8][84] = 12,
	[8][85] = 12,
	[8][86] = 12,
	[8][87] = 12,
	[8][88] = 12,
	[8][89] = 12,
	[8][90] = 12,
	[8][96] = 13,
	[8][97] = 12,
	[8][98] = 12,
	[8][99] = 12,
	[8][100] = 12,
	[8][101] = 12,
	[8][102] = 12,
	[8][103] = 12,
	[8][104] = 12,
	[8][105] = 12,
	[8][106] = 12,
	[8][107] = 12,
	[8][108] = 12,
	[8][109] = 12,
	[8][110] = 12,
	[8][111] = 12,
	[8][112] = 12,
	[8][113] = 12,
	[8][114] = 12,
	[8][115] = 12,
	[8][116] = 12,
	[8][117] = 12,
	[8][118] = 12,
	[8][119] = 12,
	[8][120] = 12,
	[8][121] = 12,
	[8][122] = 12,
	[11][48] = 11,
	[11][49] = 11,
	[11][50] = 11,
	[11][51] = 11,
	[11][52] = 11,
	[11][53] = 11,
	[11][54] = 11,
	[11][55] = 11,
	[11][56] = 11,
	[11][57] = 11,
	[12][65] = 12,
	[12][66] = 12,
	[12][67] = 12,
	[12][68] = 12,
	[12][69] = 12,
	[12][70] = 12,
	[12][71] = 12,
	[12][72] = 12,
	[12][73] = 12,
	[12][74] = 12,
	[12][75] = 12,
	[12][76] = 12,
	[12][77] = 12,
	[12][78] = 12,
	[12][79] = 12,
	[12][80] = 12,
	[12][81] = 12,
	[12][82] = 12,
	[12][83] = 12,
	[12][84] = 12,
	[12][85] = 12,
	[12][86] = 12,
	[12][87] = 12,
	[12][88] = 12,
	[12][89] = 12,
	[12][90] = 12,
	[12][97] = 12,
	[12][98] = 12,
	[12][99] = 12,
	[12][100] = 12,
	[12][101] = 12,
	[12][102] = 12,
	[12][103] = 12,
	[12][104] = 12,
	[12][105] = 12,
	[12][106] = 12,
	[12][107] = 12,
	[12][108] = 12,
	[12][109] = 12,
	[12][110] = 12,
	[12][111] = 12,
	[12][112] = 12,
	[12][113] = 12,
	[12][114] = 12,
	[12][115] = 12,
	[12][116] = 12,
	[12][117] = 12,
	[12][118] = 12,
	[12][119] = 12,
	[12][120] = 12,
	[12][121] = 12,
	[12][122] = 12,
};
const unsigned zebu_starts[23] = {
	[1] = 1,
	[2] = 6,
	[3] = 6,
	[4] = 1,
	[5] = 1,
	[6] = 8,
	[7] = 8,
	[8] = 1,
	[9] = 1,
	[10] = 8,
	[11] = 8,
	[12] = 8,
	[13] = 8,
	[14] = 8,
	[15] = 8,
	[16] = 8,
	[17] = 6,
	[18] = 6,
	[19] = 8,
	[20] = 6,
	[21] = 6,
	[22] = 6,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[7] = {
	[6] = 7,
};
const unsigned zebu_accepts[14] = {
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 5,
	[7] = 6,
	[9] = 2,
	[10] = 8,
	[11] = 3,
	[12] = 4,
	[13] = 5,
};
const unsigned start_grammar_id = 10;
const char* zebu_grammar_names[12] = {
	[10] = "(start)",
	[9] = "(trie #1)",
	[7] = "value",
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










