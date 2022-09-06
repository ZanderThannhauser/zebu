#include "json.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const unsigned zebu_lexer[25][126] = {
	[1][32] = 1,
	[1][34] = 7,
	[1][48] = 8,
	[1][49] = 8,
	[1][50] = 8,
	[1][51] = 8,
	[1][52] = 8,
	[1][53] = 8,
	[1][54] = 8,
	[1][55] = 8,
	[1][56] = 8,
	[1][57] = 8,
	[1][91] = 9,
	[1][102] = 10,
	[1][116] = 11,
	[1][123] = 12,
	[2][32] = 2,
	[3][32] = 3,
	[3][34] = 7,
	[4][32] = 4,
	[4][44] = 14,
	[4][93] = 15,
	[5][32] = 5,
	[5][58] = 16,
	[6][32] = 6,
	[6][44] = 14,
	[6][125] = 17,
	[7][97] = 18,
	[7][98] = 18,
	[7][99] = 18,
	[7][100] = 18,
	[7][101] = 18,
	[7][102] = 18,
	[7][103] = 18,
	[7][104] = 18,
	[7][105] = 18,
	[7][106] = 18,
	[7][107] = 18,
	[7][108] = 18,
	[7][109] = 18,
	[7][110] = 18,
	[7][111] = 18,
	[7][112] = 18,
	[7][113] = 18,
	[7][114] = 18,
	[7][115] = 18,
	[7][116] = 18,
	[7][117] = 18,
	[7][118] = 18,
	[7][119] = 18,
	[7][120] = 18,
	[7][121] = 18,
	[7][122] = 18,
	[8][48] = 8,
	[8][49] = 8,
	[8][50] = 8,
	[8][51] = 8,
	[8][52] = 8,
	[8][53] = 8,
	[8][54] = 8,
	[8][55] = 8,
	[8][56] = 8,
	[8][57] = 8,
	[10][97] = 19,
	[11][114] = 20,
	[18][34] = 21,
	[18][97] = 18,
	[18][98] = 18,
	[18][99] = 18,
	[18][100] = 18,
	[18][101] = 18,
	[18][102] = 18,
	[18][103] = 18,
	[18][104] = 18,
	[18][105] = 18,
	[18][106] = 18,
	[18][107] = 18,
	[18][108] = 18,
	[18][109] = 18,
	[18][110] = 18,
	[18][111] = 18,
	[18][112] = 18,
	[18][113] = 18,
	[18][114] = 18,
	[18][115] = 18,
	[18][116] = 18,
	[18][117] = 18,
	[18][118] = 18,
	[18][119] = 18,
	[18][120] = 18,
	[18][121] = 18,
	[18][122] = 18,
	[19][108] = 22,
	[20][117] = 23,
	[22][115] = 24,
	[23][101] = 25,
	[24][101] = 26,
};


const unsigned zebu_lexer_starts[69] = {
	[1] = 1,
	[2] = 2,
	[3] = 2,
	[4] = 2,
	[5] = 2,
	[6] = 1,
	[7] = 3,
	[8] = 2,
	[9] = 4,
	[10] = 4,
	[11] = 4,
	[12] = 4,
	[13] = 1,
	[14] = 3,
	[15] = 4,
	[16] = 5,
	[17] = 4,
	[18] = 5,
	[19] = 1,
	[20] = 2,
	[21] = 2,
	[22] = 1,
	[23] = 1,
	[24] = 4,
	[25] = 4,
	[26] = 1,
	[27] = 4,
	[28] = 6,
	[29] = 6,
	[30] = 6,
	[31] = 6,
	[32] = 1,
	[33] = 3,
	[34] = 6,
	[35] = 4,
	[36] = 6,
	[37] = 2,
	[38] = 4,
	[39] = 5,
	[40] = 3,
	[41] = 2,
	[42] = 2,
	[43] = 4,
	[44] = 3,
	[45] = 4,
	[46] = 4,
	[47] = 1,
	[48] = 6,
	[49] = 6,
	[50] = 1,
	[51] = 5,
	[52] = 5,
	[53] = 4,
	[54] = 6,
	[55] = 1,
	[56] = 1,
	[57] = 6,
	[58] = 3,
	[59] = 6,
	[60] = 6,
	[61] = 6,
	[62] = 6,
	[63] = 5,
	[64] = 2,
	[65] = 4,
	[66] = 1,
	[67] = 6,
	[68] = 6,
};


const unsigned zebu_lexer_defaults[1] = {
};


const unsigned zebu_lexer_accepts[27] = {
	[8] = 4,
	[9] = 6,
	[12] = 7,
	[13] = 8,
	[14] = 9,
	[15] = 10,
	[16] = 11,
	[17] = 12,
	[21] = 5,
	[25] = 2,
	[26] = 3,
};


const unsigned zebu_lexer_EOFs[3] = {
	[2] = 13,
};


const unsigned zebu_shifts[68][13] = {
	[1][2] = 2,
	[1][3] = 3,
	[1][4] = 4,
	[1][5] = 5,
	[1][6] = 6,
	[1][7] = 7,
	[6][2] = 9,
	[6][3] = 10,
	[6][4] = 11,
	[6][5] = 12,
	[6][6] = 13,
	[6][7] = 14,
	[7][5] = 16,
	[13][2] = 9,
	[13][3] = 10,
	[13][4] = 11,
	[13][5] = 12,
	[13][6] = 13,
	[13][7] = 14,
	[14][5] = 18,
	[15][9] = 19,
	[15][10] = 20,
	[16][11] = 22,
	[17][9] = 23,
	[17][10] = 24,
	[18][11] = 26,
	[19][2] = 9,
	[19][3] = 10,
	[19][4] = 11,
	[19][5] = 12,
	[19][6] = 13,
	[19][7] = 14,
	[22][2] = 28,
	[22][3] = 29,
	[22][4] = 30,
	[22][5] = 31,
	[22][6] = 32,
	[22][7] = 33,
	[23][2] = 9,
	[23][3] = 10,
	[23][4] = 11,
	[23][5] = 12,
	[23][6] = 13,
	[23][7] = 14,
	[26][2] = 28,
	[26][3] = 29,
	[26][4] = 30,
	[26][5] = 31,
	[26][6] = 32,
	[26][7] = 33,
	[27][9] = 19,
	[27][10] = 20,
	[32][2] = 9,
	[32][3] = 10,
	[32][4] = 11,
	[32][5] = 12,
	[32][6] = 13,
	[32][7] = 14,
	[33][5] = 39,
	[34][9] = 40,
	[34][12] = 41,
	[35][9] = 23,
	[35][10] = 24,
	[36][9] = 44,
	[36][12] = 45,
	[38][9] = 47,
	[38][10] = 48,
	[39][11] = 50,
	[40][5] = 51,
	[44][5] = 52,
	[47][2] = 9,
	[47][3] = 10,
	[47][4] = 11,
	[47][5] = 12,
	[47][6] = 13,
	[47][7] = 14,
	[50][2] = 28,
	[50][3] = 29,
	[50][4] = 30,
	[50][5] = 31,
	[50][6] = 32,
	[50][7] = 33,
	[51][11] = 55,
	[52][11] = 56,
	[53][9] = 47,
	[53][10] = 48,
	[54][9] = 58,
	[54][12] = 59,
	[55][2] = 28,
	[55][3] = 29,
	[55][4] = 30,
	[55][5] = 31,
	[55][6] = 32,
	[55][7] = 33,
	[56][2] = 28,
	[56][3] = 29,
	[56][4] = 30,
	[56][5] = 31,
	[56][6] = 32,
	[56][7] = 33,
	[58][5] = 63,
	[61][9] = 40,
	[61][12] = 41,
	[62][9] = 44,
	[62][12] = 45,
	[63][11] = 66,
	[66][2] = 28,
	[66][3] = 29,
	[66][4] = 30,
	[66][5] = 31,
	[66][6] = 32,
	[66][7] = 33,
	[67][9] = 58,
	[67][12] = 59,
};


const unsigned zebu_reduces[69][13] = {
	[2][8] = 1,
	[3][8] = 2,
	[4][8] = 3,
	[5][8] = 4,
	[8][8] = 5,
	[9][9] = 1,
	[9][10] = 1,
	[10][9] = 2,
	[10][10] = 2,
	[11][9] = 3,
	[11][10] = 3,
	[12][9] = 4,
	[12][10] = 4,
	[20][8] = 6,
	[21][8] = 7,
	[24][9] = 6,
	[24][10] = 6,
	[25][9] = 7,
	[25][10] = 7,
	[28][9] = 1,
	[28][12] = 1,
	[29][9] = 2,
	[29][12] = 2,
	[30][9] = 3,
	[30][12] = 3,
	[31][9] = 4,
	[31][12] = 4,
	[37][8] = 8,
	[41][8] = 9,
	[42][8] = 10,
	[43][9] = 8,
	[43][10] = 8,
	[45][9] = 9,
	[45][10] = 9,
	[46][9] = 10,
	[46][10] = 10,
	[48][9] = 6,
	[48][12] = 6,
	[49][9] = 7,
	[49][12] = 7,
	[57][9] = 8,
	[57][12] = 8,
	[59][9] = 9,
	[59][12] = 9,
	[60][9] = 10,
	[60][12] = 10,
	[64][8] = 11,
	[65][9] = 11,
	[65][10] = 11,
	[68][9] = 11,
	[68][12] = 11,
};


const unsigned zebu_gotos[68][4] = {
	[1][1] = 8,
	[6][1] = 15,
	[13][1] = 17,
	[15][2] = 21,
	[17][2] = 25,
	[19][1] = 27,
	[22][1] = 34,
	[23][1] = 35,
	[26][1] = 36,
	[27][2] = 37,
	[32][1] = 38,
	[34][3] = 42,
	[35][2] = 43,
	[36][3] = 46,
	[38][2] = 49,
	[47][1] = 53,
	[50][1] = 54,
	[53][2] = 57,
	[54][3] = 60,
	[55][1] = 61,
	[56][1] = 62,
	[61][3] = 64,
	[62][3] = 65,
	[66][1] = 67,
	[67][3] = 68,
};


struct token
{
unsigned char* data;
unsigned len;
};
struct __start__
{
	struct value* value;
};

struct value
{
	struct token* boolean;
	struct value* element;
	struct token* key;
	struct token* number;
	struct token* string;
	struct value* value;
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

void print_value_tree(struct link* links, enum prefix p, const char* name, struct value* ptree);

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
	if (ptree->value)
		print_value_tree(new ?: links, p_last_child, "value", ptree->value);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "value");
	free(new);
}
void print_value_tree(struct link* links, enum prefix p, const char* name, struct value* ptree)
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
	printf("\e[34m%s\e[m (\e[36mvalue\e[m)\n", name);
	if (ptree->boolean)
		print_token_leaf(new ?: links, p_not_last_child, "boolean", ptree->boolean);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "boolean");
	if (ptree->element)
		print_value_tree(new ?: links, p_not_last_child, "element", ptree->element);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "value", "element");
	if (ptree->key)
		print_token_leaf(new ?: links, p_not_last_child, "key", ptree->key);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "key");
	if (ptree->number)
		print_token_leaf(new ?: links, p_not_last_child, "number", ptree->number);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "number");
	if (ptree->string)
		print_token_leaf(new ?: links, p_not_last_child, "string", ptree->string);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "string");
	if (ptree->value)
		print_value_tree(new ?: links, p_last_child, "value", ptree->value);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "value");
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

void free_value_tree(struct value* ptree);

void free___start___tree(struct __start__* ptree)
{
	if (ptree)
	{
		free_value_tree(ptree->value);
		free(ptree);
	}
}

void free_value_tree(struct value* ptree)
{
	if (ptree)
	{
		free_token(ptree->boolean);
		free_value_tree(ptree->element);
		free_token(ptree->key);
		free_token(ptree->number);
		free_token(ptree->string);
		free_value_tree(ptree->value);
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
	case 6:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 8:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->element) { free_value_tree(value->element); value->element = trie->element; }
			if (trie->key) { free_token(value->key); value->key = trie->key; }
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			if (trie->value) { free_value_tree(value->value); value->value = trie->value; }
			free(trie);
		};
		free_value_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 11:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->element) { free_value_tree(value->element); value->element = trie->element; }
			if (trie->key) { free_token(value->key); value->key = trie->key; }
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			if (trie->value) { free_value_tree(value->value); value->value = trie->value; }
			free(trie);
		};
		free_value_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 9:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 5:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_value_tree(value->value), value->value = data.data[--yacc.n, --data.n];
		d = value, g = 4;
		break;
	}
	case 7:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->element) { free_value_tree(value->element); value->element = trie->element; }
			if (trie->key) { free_token(value->key); value->key = trie->key; }
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			if (trie->value) { free_value_tree(value->value); value->value = trie->value; }
			free(trie);
		};
		free_value_tree(value->element), value->element = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 3:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(value->number), value->number = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(value->boolean), value->boolean = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 10:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->element) { free_value_tree(value->element); value->element = trie->element; }
			if (trie->key) { free_token(value->key); value->key = trie->key; }
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			if (trie->value) { free_value_tree(value->value); value->value = trie->value; }
			free(trie);
		};
		free_value_tree(value->value), value->value = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->key), value->key = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 4:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(value->string), value->string = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 2:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(value->boolean), value->boolean = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
}
				
				if (g == 4)
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










