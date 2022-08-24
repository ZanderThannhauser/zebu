const unsigned zebu_shifts[21][23] = {
	[1][2] = 8,
	[1][3] = 2,
	[1][4] = 14,
	[1][5] = 18,
	[1][6] = 4,
	[1][7] = 20,
	[1][8] = 11,
	[1][9] = 13,
	[1][10] = 15,
	[1][11] = 17,
	[1][12] = 6,
	[1][13] = 19,
	[1][14] = 10,
	[1][15] = 12,
	[1][16] = 16,
	[2][17] = 3,
	[4][17] = 3,
	[4][20] = 5,
	[6][17] = 3,
	[6][20] = 5,
	[6][21] = 7,
	[8][17] = 3,
	[8][20] = 5,
	[8][21] = 7,
	[8][22] = 9,
	[10][17] = 3,
	[10][20] = 5,
	[10][22] = 9,
	[11][17] = 3,
	[11][21] = 7,
	[12][17] = 3,
	[12][21] = 7,
	[12][22] = 9,
	[13][17] = 3,
	[13][22] = 9,
	[14][20] = 5,
	[15][20] = 5,
	[15][21] = 7,
	[16][20] = 5,
	[16][21] = 7,
	[16][22] = 9,
	[17][20] = 5,
	[17][22] = 9,
	[18][21] = 7,
	[19][21] = 7,
	[19][22] = 9,
	[20][22] = 9,
};
const unsigned zebu_reduces[10][19] = {
	[3][18] = 19,
	[5][18] = 19,
	[7][18] = 19,
	[9][18] = 19,
};
const unsigned zebu_popcounts[10][19] = {
	[3][18] = 2,
	[5][18] = 2,
	[7][18] = 2,
	[9][18] = 2,
};
const unsigned zebu_lexer[260][98] = {
	[1][97] = 2,
	[2][97] = 3,
	[3][97] = 4,
	[4][97] = 5,
	[5][97] = 6,
	[6][97] = 7,
	[7][97] = 8,
	[8][97] = 9,
	[9][97] = 10,
	[10][97] = 11,
	[11][97] = 12,
	[12][97] = 13,
	[13][97] = 14,
	[14][97] = 15,
	[15][97] = 16,
	[16][97] = 17,
	[17][97] = 18,
	[18][97] = 19,
	[19][97] = 20,
	[20][97] = 21,
	[21][97] = 22,
	[22][97] = 23,
	[23][97] = 24,
	[24][97] = 25,
	[25][97] = 26,
	[26][97] = 27,
	[27][97] = 28,
	[28][97] = 29,
	[29][97] = 30,
	[30][97] = 31,
	[31][97] = 32,
	[32][97] = 33,
	[33][97] = 34,
	[34][97] = 35,
	[35][97] = 36,
	[36][97] = 37,
	[37][97] = 38,
	[38][97] = 39,
	[39][97] = 40,
	[40][97] = 41,
	[41][97] = 42,
	[42][97] = 43,
	[43][97] = 44,
	[44][97] = 45,
	[45][97] = 46,
	[46][97] = 47,
	[47][97] = 48,
	[48][97] = 49,
	[49][97] = 50,
	[50][97] = 51,
	[51][97] = 52,
	[52][97] = 53,
	[53][97] = 54,
	[54][97] = 55,
	[55][97] = 56,
	[56][97] = 57,
	[57][97] = 58,
	[58][97] = 59,
	[59][97] = 60,
	[60][97] = 61,
	[61][97] = 62,
	[62][97] = 63,
	[63][97] = 64,
	[64][97] = 65,
	[65][97] = 66,
	[66][97] = 67,
	[67][97] = 68,
	[68][97] = 69,
	[69][97] = 70,
	[70][97] = 71,
	[71][97] = 72,
	[72][97] = 73,
	[73][97] = 74,
	[74][97] = 75,
	[75][97] = 76,
	[76][97] = 77,
	[77][97] = 78,
	[78][97] = 79,
	[79][97] = 80,
	[80][97] = 81,
	[81][97] = 82,
	[82][97] = 83,
	[83][97] = 84,
	[84][97] = 85,
	[85][97] = 86,
	[86][97] = 87,
	[87][97] = 88,
	[88][97] = 89,
	[89][97] = 90,
	[90][97] = 91,
	[91][97] = 92,
	[92][97] = 93,
	[93][97] = 94,
	[94][97] = 95,
	[95][97] = 96,
	[96][97] = 97,
	[97][97] = 98,
	[98][97] = 99,
	[99][97] = 100,
	[100][97] = 101,
	[101][97] = 102,
	[102][97] = 103,
	[103][97] = 104,
	[104][97] = 105,
	[105][97] = 106,
	[106][97] = 107,
	[107][97] = 108,
	[108][97] = 109,
	[109][97] = 110,
	[110][97] = 111,
	[111][97] = 112,
	[112][97] = 113,
	[113][97] = 114,
	[114][97] = 115,
	[115][97] = 116,
	[116][97] = 117,
	[117][97] = 118,
	[118][97] = 119,
	[119][97] = 120,
	[120][97] = 121,
	[121][97] = 122,
	[122][97] = 123,
	[123][97] = 124,
	[124][97] = 125,
	[125][97] = 126,
	[126][97] = 127,
	[127][97] = 128,
	[128][97] = 129,
	[129][97] = 130,
	[130][97] = 131,
	[131][97] = 132,
	[132][97] = 133,
	[133][97] = 134,
	[134][97] = 135,
	[135][97] = 136,
	[136][97] = 137,
	[137][97] = 138,
	[138][97] = 139,
	[139][97] = 140,
	[140][97] = 141,
	[141][97] = 142,
	[142][97] = 143,
	[143][97] = 144,
	[144][97] = 145,
	[145][97] = 146,
	[146][97] = 147,
	[147][97] = 148,
	[148][97] = 149,
	[149][97] = 150,
	[150][97] = 151,
	[151][97] = 152,
	[152][97] = 153,
	[153][97] = 154,
	[154][97] = 155,
	[155][97] = 156,
	[156][97] = 157,
	[157][97] = 158,
	[158][97] = 159,
	[159][97] = 160,
	[160][97] = 161,
	[161][97] = 162,
	[162][97] = 163,
	[163][97] = 164,
	[164][97] = 165,
	[165][97] = 166,
	[166][97] = 167,
	[167][97] = 168,
	[168][97] = 169,
	[169][97] = 170,
	[170][97] = 171,
	[171][97] = 172,
	[172][97] = 173,
	[173][97] = 174,
	[174][97] = 175,
	[175][97] = 176,
	[176][97] = 177,
	[177][97] = 178,
	[178][97] = 179,
	[179][97] = 180,
	[180][97] = 181,
	[181][97] = 182,
	[182][97] = 183,
	[183][97] = 184,
	[184][97] = 185,
	[185][97] = 186,
	[186][97] = 187,
	[187][97] = 188,
	[188][97] = 189,
	[189][97] = 190,
	[190][97] = 191,
	[191][97] = 192,
	[192][97] = 193,
	[193][97] = 194,
	[194][97] = 195,
	[195][97] = 196,
	[196][97] = 197,
	[197][97] = 198,
	[198][97] = 199,
	[199][97] = 200,
	[200][97] = 201,
	[201][97] = 202,
	[202][97] = 203,
	[203][97] = 204,
	[204][97] = 205,
	[205][97] = 206,
	[206][97] = 207,
	[207][97] = 208,
	[208][97] = 209,
	[209][97] = 210,
	[210][97] = 211,
	[211][97] = 2,
	[212][49] = 213,
	[216][49] = 217,
	[216][50] = 218,
	[219][49] = 220,
	[219][50] = 221,
	[219][51] = 222,
	[223][49] = 224,
	[223][50] = 225,
	[223][51] = 226,
	[223][52] = 227,
	[228][49] = 229,
	[228][50] = 230,
	[228][52] = 231,
	[232][49] = 233,
	[232][51] = 234,
	[235][49] = 236,
	[235][51] = 237,
	[235][52] = 238,
	[239][49] = 240,
	[239][52] = 241,
	[242][50] = 243,
	[244][50] = 245,
	[244][51] = 246,
	[247][50] = 248,
	[247][51] = 249,
	[247][52] = 250,
	[251][50] = 252,
	[251][52] = 253,
	[254][51] = 255,
	[256][51] = 257,
	[256][52] = 258,
	[259][52] = 260,
};
const unsigned zebu_starts[21] = {
	[1] = 1,
	[2] = 212,
	[3] = 214,
	[4] = 216,
	[5] = 214,
	[6] = 219,
	[7] = 214,
	[8] = 223,
	[9] = 214,
	[10] = 228,
	[11] = 232,
	[12] = 235,
	[13] = 239,
	[14] = 242,
	[15] = 244,
	[16] = 247,
	[17] = 251,
	[18] = 254,
	[19] = 256,
	[20] = 259,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[215] = {
	[214] = 215,
};
const unsigned zebu_accepts[261] = {
	[3] = 3,
	[4] = 4,
	[5] = 3,
	[6] = 5,
	[7] = 6,
	[8] = 7,
	[9] = 3,
	[10] = 4,
	[11] = 8,
	[13] = 6,
	[15] = 9,
	[16] = 10,
	[17] = 3,
	[19] = 6,
	[21] = 8,
	[22] = 11,
	[23] = 3,
	[25] = 6,
	[26] = 5,
	[27] = 3,
	[28] = 4,
	[29] = 9,
	[31] = 12,
	[33] = 3,
	[34] = 4,
	[35] = 3,
	[36] = 13,
	[37] = 6,
	[39] = 3,
	[40] = 4,
	[41] = 8,
	[43] = 14,
	[45] = 3,
	[46] = 10,
	[47] = 3,
	[49] = 6,
	[50] = 7,
	[51] = 8,
	[52] = 4,
	[53] = 3,
	[55] = 6,
	[56] = 5,
	[57] = 9,
	[58] = 4,
	[59] = 3,
	[61] = 12,
	[63] = 3,
	[64] = 11,
	[65] = 3,
	[66] = 5,
	[67] = 6,
	[69] = 3,
	[70] = 4,
	[71] = 15,
	[73] = 6,
	[75] = 3,
	[76] = 10,
	[77] = 3,
	[78] = 7,
	[79] = 6,
	[81] = 8,
	[82] = 4,
	[83] = 3,
	[85] = 14,
	[86] = 5,
	[87] = 3,
	[88] = 4,
	[89] = 3,
	[91] = 12,
	[92] = 7,
	[93] = 3,
	[94] = 4,
	[95] = 3,
	[96] = 5,
	[97] = 6,
	[99] = 9,
	[100] = 4,
	[101] = 8,
	[103] = 6,
	[105] = 3,
	[106] = 16,
	[107] = 3,
	[109] = 6,
	[111] = 8,
	[112] = 4,
	[113] = 9,
	[115] = 6,
	[116] = 5,
	[117] = 3,
	[118] = 4,
	[119] = 3,
	[120] = 7,
	[121] = 12,
	[123] = 3,
	[124] = 4,
	[125] = 3,
	[126] = 5,
	[127] = 14,
	[129] = 3,
	[130] = 4,
	[131] = 8,
	[133] = 6,
	[134] = 7,
	[135] = 3,
	[136] = 10,
	[137] = 3,
	[139] = 6,
	[141] = 15,
	[142] = 4,
	[143] = 3,
	[145] = 6,
	[146] = 5,
	[147] = 3,
	[148] = 11,
	[149] = 3,
	[151] = 12,
	[153] = 3,
	[154] = 4,
	[155] = 9,
	[156] = 5,
	[157] = 6,
	[159] = 3,
	[160] = 4,
	[161] = 8,
	[162] = 7,
	[163] = 6,
	[165] = 3,
	[166] = 10,
	[167] = 3,
	[169] = 14,
	[171] = 8,
	[172] = 4,
	[173] = 3,
	[175] = 6,
	[176] = 13,
	[177] = 3,
	[178] = 4,
	[179] = 3,
	[181] = 12,
	[183] = 9,
	[184] = 4,
	[185] = 3,
	[186] = 5,
	[187] = 6,
	[189] = 3,
	[190] = 11,
	[191] = 8,
	[193] = 6,
	[195] = 3,
	[196] = 10,
	[197] = 9,
	[199] = 6,
	[201] = 8,
	[202] = 4,
	[203] = 3,
	[204] = 7,
	[205] = 6,
	[206] = 5,
	[207] = 3,
	[208] = 4,
	[209] = 3,
	[211] = 2,
	[213] = 17,
	[215] = 18,
	[217] = 17,
	[218] = 20,
	[220] = 17,
	[221] = 20,
	[222] = 21,
	[224] = 17,
	[225] = 20,
	[226] = 21,
	[227] = 22,
	[229] = 17,
	[230] = 20,
	[231] = 22,
	[233] = 17,
	[234] = 21,
	[236] = 17,
	[237] = 21,
	[238] = 22,
	[240] = 17,
	[241] = 22,
	[243] = 20,
	[245] = 20,
	[246] = 21,
	[248] = 20,
	[249] = 21,
	[250] = 22,
	[252] = 20,
	[253] = 22,
	[255] = 21,
	[257] = 21,
	[258] = 22,
	[260] = 22,
};
const unsigned start_grammar_id = 19;
const char* zebu_grammar_names[24] = {
	[19] = "(start)",
};
const char* zebu_token_names[24] = {
	[1] = "0",
	[3] = "1",
	[6] = "1, 3",
	[12] = "1, 3, 5",
	[2] = "1, 3, 5, 7",
	[14] = "1, 3, 7",
	[8] = "1, 5",
	[15] = "1, 5, 7",
	[9] = "1, 7",
	[17] = "2",
	[4] = "3",
	[10] = "3, 5",
	[16] = "3, 5, 7",
	[11] = "3, 7",
	[20] = "4",
	[5] = "5",
	[13] = "5, 7",
	[21] = "6",
	[7] = "7",
	[22] = "8",
	[18] = "9",
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










