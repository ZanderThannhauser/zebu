#include "explode.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const unsigned zebu_lexer[233][98] = {
	[1][97] = 18,
	[2][50] = 19,
	[3][50] = 19,
	[3][51] = 20,
	[4][50] = 19,
	[4][51] = 20,
	[4][53] = 21,
	[5][50] = 19,
	[5][51] = 20,
	[5][53] = 21,
	[5][55] = 22,
	[6][50] = 19,
	[6][51] = 20,
	[6][55] = 22,
	[7][50] = 19,
	[7][53] = 21,
	[8][50] = 19,
	[8][53] = 21,
	[8][55] = 22,
	[9][50] = 19,
	[9][55] = 22,
	[10][51] = 20,
	[11][51] = 20,
	[11][53] = 21,
	[12][51] = 20,
	[12][53] = 21,
	[12][55] = 22,
	[13][51] = 20,
	[13][55] = 22,
	[14][53] = 21,
	[15][53] = 21,
	[15][55] = 22,
	[16][55] = 22,
	[18][97] = 24,
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
	[211][97] = 212,
	[212][97] = 213,
	[213][97] = 214,
	[214][97] = 215,
	[215][97] = 216,
	[216][97] = 217,
	[217][97] = 218,
	[218][97] = 219,
	[219][97] = 220,
	[220][97] = 221,
	[221][97] = 222,
	[222][97] = 223,
	[223][97] = 224,
	[224][97] = 225,
	[225][97] = 226,
	[226][97] = 227,
	[227][97] = 228,
	[228][97] = 229,
	[229][97] = 230,
	[230][97] = 231,
	[231][97] = 232,
	[232][97] = 18,
};


const unsigned zebu_lexer_starts[21] = {
	[1] = 1,
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 5,
	[6] = 6,
	[7] = 7,
	[8] = 8,
	[9] = 9,
	[10] = 10,
	[11] = 11,
	[12] = 12,
	[13] = 13,
	[14] = 14,
	[15] = 15,
	[16] = 16,
	[17] = 17,
	[18] = 17,
	[19] = 17,
	[20] = 17,
};


const unsigned zebu_lexer_defaults[1] = {
};


const unsigned zebu_lexer_accepts[233] = {
	[19] = 17,
	[20] = 18,
	[21] = 19,
	[22] = 20,
	[23] = 21,
	[24] = 2,
	[25] = 10,
	[26] = 2,
	[27] = 14,
	[28] = 3,
	[29] = 16,
	[30] = 2,
	[31] = 10,
	[32] = 7,
	[34] = 3,
	[36] = 9,
	[37] = 11,
	[38] = 2,
	[40] = 3,
	[42] = 7,
	[43] = 13,
	[44] = 2,
	[46] = 3,
	[47] = 14,
	[48] = 2,
	[49] = 10,
	[50] = 9,
	[52] = 4,
	[54] = 2,
	[55] = 10,
	[56] = 2,
	[57] = 15,
	[58] = 3,
	[60] = 2,
	[61] = 10,
	[62] = 7,
	[64] = 6,
	[66] = 2,
	[67] = 11,
	[68] = 2,
	[70] = 3,
	[71] = 16,
	[72] = 7,
	[73] = 10,
	[74] = 2,
	[76] = 3,
	[77] = 14,
	[78] = 9,
	[79] = 10,
	[80] = 2,
	[82] = 4,
	[84] = 2,
	[85] = 13,
	[86] = 2,
	[87] = 14,
	[88] = 3,
	[90] = 2,
	[91] = 10,
	[92] = 8,
	[94] = 3,
	[96] = 2,
	[97] = 11,
	[98] = 2,
	[99] = 16,
	[100] = 3,
	[102] = 7,
	[103] = 10,
	[104] = 2,
	[106] = 6,
	[107] = 14,
	[108] = 2,
	[109] = 10,
	[110] = 2,
	[112] = 4,
	[113] = 16,
	[114] = 2,
	[115] = 10,
	[116] = 2,
	[117] = 14,
	[118] = 3,
	[120] = 9,
	[121] = 10,
	[122] = 7,
	[124] = 3,
	[126] = 2,
	[127] = 12,
	[128] = 2,
	[130] = 3,
	[132] = 7,
	[133] = 10,
	[134] = 9,
	[136] = 3,
	[137] = 14,
	[138] = 2,
	[139] = 10,
	[140] = 2,
	[141] = 16,
	[142] = 4,
	[144] = 2,
	[145] = 10,
	[146] = 2,
	[147] = 14,
	[148] = 6,
	[150] = 2,
	[151] = 10,
	[152] = 7,
	[154] = 3,
	[155] = 16,
	[156] = 2,
	[157] = 11,
	[158] = 2,
	[160] = 3,
	[162] = 8,
	[163] = 10,
	[164] = 2,
	[166] = 3,
	[167] = 14,
	[168] = 2,
	[169] = 13,
	[170] = 2,
	[172] = 4,
	[174] = 2,
	[175] = 10,
	[176] = 9,
	[177] = 14,
	[178] = 3,
	[180] = 2,
	[181] = 10,
	[182] = 7,
	[183] = 16,
	[184] = 3,
	[186] = 2,
	[187] = 11,
	[188] = 2,
	[190] = 6,
	[192] = 7,
	[193] = 10,
	[194] = 2,
	[196] = 3,
	[197] = 15,
	[198] = 2,
	[199] = 10,
	[200] = 2,
	[202] = 4,
	[204] = 9,
	[205] = 10,
	[206] = 2,
	[207] = 14,
	[208] = 3,
	[210] = 2,
	[211] = 13,
	[212] = 7,
	[214] = 3,
	[216] = 2,
	[217] = 11,
	[218] = 9,
	[220] = 3,
	[222] = 7,
	[223] = 10,
	[224] = 2,
	[225] = 16,
	[226] = 3,
	[227] = 14,
	[228] = 2,
	[229] = 10,
	[230] = 2,
	[232] = 5,
};


const unsigned zebu_lexer_EOFs[18] = {
	[17] = 23,
};


const unsigned zebu_shifts[17][21] = {
	[1][2] = 2,
	[1][3] = 3,
	[1][4] = 4,
	[1][5] = 5,
	[1][6] = 6,
	[1][7] = 7,
	[1][8] = 8,
	[1][9] = 9,
	[1][10] = 10,
	[1][11] = 11,
	[1][12] = 12,
	[1][13] = 13,
	[1][14] = 14,
	[1][15] = 15,
	[1][16] = 16,
	[2][17] = 17,
	[3][17] = 17,
	[3][18] = 18,
	[4][17] = 17,
	[4][18] = 18,
	[4][19] = 19,
	[5][17] = 17,
	[5][18] = 18,
	[5][19] = 19,
	[5][20] = 20,
	[6][17] = 17,
	[6][18] = 18,
	[6][20] = 20,
	[7][17] = 17,
	[7][19] = 19,
	[8][17] = 17,
	[8][19] = 19,
	[8][20] = 20,
	[9][17] = 17,
	[9][20] = 20,
	[10][18] = 18,
	[11][18] = 18,
	[11][19] = 19,
	[12][18] = 18,
	[12][19] = 19,
	[12][20] = 20,
	[13][18] = 18,
	[13][20] = 20,
	[14][19] = 19,
	[15][19] = 19,
	[15][20] = 20,
	[16][20] = 20,
};


const unsigned zebu_reduces[21][22] = {
	[17][21] = 1,
	[18][21] = 2,
	[19][21] = 3,
	[20][21] = 4,
};


const unsigned zebu_gotos[1][1] = {
};


struct token
{
unsigned char* data;
unsigned len;
};
struct __start__
{
	struct token* multiple2;
	struct token* multiple3;
	struct token* multiple5;
	struct token* multiple7;
};



#include <stdbool.h>

struct link
{
	bool is_last;
	struct link* prev;
};

void print_links(struct link* link)
{
	if (!link) return;
	
	print_links(link->prev);
	
	if (link->is_last)
		fputs("    ", stdout);
	else
		fputs("│   ", stdout);
}

enum prefix
{
	p_root,
	p_not_last_child,
	p_last_child,
};

void print_token_leaf(struct link* links, enum prefix p, const char* name, struct token* token)
{
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[32m%s\e[0m (\e[35m\"%s\"\e[0m)\n", name, token->data);
}

void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name)
{
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[31m%s\e[0m (\e[36m%s\e[0m)\n", name, type);
}
void print___start___tree(struct link* links, enum prefix p, const char* name, struct __start__* ptree);

void print___start___tree(struct link* links, enum prefix p, const char* name, struct __start__* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__start__\e[m)\n", name);
	if (ptree->multiple2)
		print_token_leaf(new ?: links, p_not_last_child, "multiple2", ptree->multiple2);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "multiple2");
	if (ptree->multiple3)
		print_token_leaf(new ?: links, p_not_last_child, "multiple3", ptree->multiple3);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "multiple3");
	if (ptree->multiple5)
		print_token_leaf(new ?: links, p_not_last_child, "multiple5", ptree->multiple5);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "multiple5");
	if (ptree->multiple7)
		print_token_leaf(new ?: links, p_last_child, "multiple7", ptree->multiple7);
	else
		print_empty_leaf(new ?: links, p_last_child, "token", "multiple7");
	free(new);
}


void free_token(struct token* this)
{
	if (this)
	{
		free(this->data);
		free(this);
	}
}
void free___start___tree(struct __start__* ptree);

void free___start___tree(struct __start__* ptree)
{
	if (ptree)
	{
		free_token(ptree->multiple2);
		free_token(ptree->multiple3);
		free_token(ptree->multiple5);
		free_token(ptree->multiple7);
		free(ptree);
	}
}



#define N(array) (sizeof(array) / sizeof(*array))

static void escape(char *out, char in)
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

int main()
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	void ddprintf(const char* fmt, ...)
	{
		for (unsigned i = 0, n = yacc.n; i < n; i++)
			printf("%u ", yacc.data[i]);
		
		printf("| ");
		
		va_list va;
		va_start(va, fmt);
		vprintf(fmt, va);
		va_end(va);
	}

	void push_state(unsigned state)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		
		yacc.data[yacc.n++] = state;
	}
	
	void push_data(void* element)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		
		data.data[data.n++] = element;
	}
	
	for (char* line; (line = readline(">>> "));)
	{
		char* lexer = (void*) line;
		
		unsigned y, s, r, t;
		
		void* td;
		
		void read_token(unsigned l)
		{
			char escaped[10];
			
			char* begin = lexer, *f = NULL;
			
			unsigned a, b, c;
			
			while (1)
			{
				if ((c = *lexer))
				{
					escape(escaped, c);
					
					ddprintf("c = '%s' (0x%X)\n", escaped, c);
					
					a = 0
						?: (l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0)
						?: (l < N(zebu_lexer_defaults) ? zebu_lexer_defaults[l] : 0);
				}
				else
				{
					ddprintf("c == <EOF>\n");
					a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
				}
				
				b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
				
				ddprintf("lexer: %u: a = %u, b = %u\n", l, a, b);
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = lexer++;
						ddprintf("l = %u, t == %u, f = %p (saved)\n", l, t, f);
					}
					else
					{
						l = a;
						if (c) lexer++;
						ddprintf("lexer: l == %u\n", l);
					}
				}
				else if (b)
				{
					ddprintf("lexer: \"%.*s\"\n", lexer - begin, begin);
					
					struct token* token = malloc(sizeof(*token));
					token->data = (void*) strndup(begin, lexer - begin);
					t = b, td = token;
					break;
				}
				else if (t)
				{
					assert(!"172");
					#if 0
					process_token(t);
					l = zebu_starts[yacc.data[yacc.n - 1]], i = f, t = 0;
					ddprintf("l == %u, i = %u, t = %u\n", l, i, t);
					#endif
				}
				else
				{
					assert(!"TODO");
				}
			}
		}
		
		yacc.n = 0, data.n = 0, y = 1, push_state(y);
		
		read_token(zebu_lexer_starts[y]);
		
		ddprintf("y = %u, t == %u\n", y, t);
		
		void* root;
		
		while (yacc.n)
		{
			if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
			{
				y = s, push_state(y), push_data(td);
				read_token(zebu_lexer_starts[y]);
			}
			else if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
			{
				unsigned g;
				
				void* d;
				
				ddprintf("r = %u\n", r);
				
				switch (r)
{
	case 2:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->multiple3), value->multiple3 = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->multiple2), value->multiple2 = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 4:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->multiple7), value->multiple7 = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 3:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->multiple5), value->multiple5 = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
}
				
				if (g == 1)
				{
					free_token(td);
					yacc.n = 0, root = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					ddprintf("y = %u\n", y);
					
					assert(y < N(zebu_gotos) && g < N(*zebu_gotos));
					
					s = zebu_gotos[y][g];
					
					ddprintf("s = %u\n", s);
					
					y = s, push_state(y), push_data(d);
				}
			}
			else
			{
				assert(!"190");
			}
		}
		
		assert(!data.n);
		
		puts("accepted!");
		
		print___start___tree(NULL, p_root, "start", root);
		
		free___start___tree(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










