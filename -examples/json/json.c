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


const unsigned zebu_lexer_starts[54] = {
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
	[15] = 2,
	[16] = 4,
	[17] = 5,
	[18] = 2,
	[19] = 6,
	[20] = 4,
	[21] = 4,
	[22] = 4,
	[23] = 6,
	[24] = 1,
	[25] = 2,
	[26] = 1,
	[27] = 3,
	[28] = 2,
	[29] = 1,
	[30] = 4,
	[31] = 3,
	[32] = 4,
	[33] = 2,
	[34] = 6,
	[35] = 6,
	[36] = 6,
	[37] = 6,
	[38] = 1,
	[39] = 3,
	[40] = 6,
	[41] = 2,
	[42] = 4,
	[43] = 4,
	[44] = 6,
	[45] = 4,
	[46] = 6,
	[47] = 6,
	[48] = 1,
	[49] = 6,
	[50] = 3,
	[51] = 6,
	[52] = 6,
	[53] = 6,
};


const unsigned zebu_lexer_accepts[27] = {
	[8] = 5,
	[9] = 6,
	[12] = 7,
	[13] = 8,
	[14] = 9,
	[15] = 10,
	[16] = 11,
	[17] = 12,
	[21] = 2,
	[25] = 3,
	[26] = 4,
};


const unsigned zebu_lexer_EOFs[3] = {
	[2] = 13,
};


const unsigned zebu_shifts[51][13] = {
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
	[7][2] = 17,
	[13][2] = 9,
	[13][3] = 10,
	[13][4] = 11,
	[13][5] = 12,
	[13][6] = 13,
	[13][7] = 14,
	[14][2] = 17,
	[16][9] = 24,
	[16][10] = 25,
	[17][11] = 26,
	[19][9] = 27,
	[19][12] = 28,
	[21][9] = 29,
	[21][10] = 30,
	[23][9] = 31,
	[23][12] = 32,
	[24][2] = 9,
	[24][3] = 10,
	[24][4] = 11,
	[24][5] = 12,
	[24][6] = 13,
	[24][7] = 14,
	[26][2] = 34,
	[26][3] = 35,
	[26][4] = 36,
	[26][5] = 37,
	[26][6] = 38,
	[26][7] = 39,
	[27][2] = 17,
	[29][2] = 9,
	[29][3] = 10,
	[29][4] = 11,
	[29][5] = 12,
	[29][6] = 13,
	[29][7] = 14,
	[31][2] = 17,
	[38][2] = 9,
	[38][3] = 10,
	[38][4] = 11,
	[38][5] = 12,
	[38][6] = 13,
	[38][7] = 14,
	[39][2] = 17,
	[45][9] = 48,
	[45][10] = 49,
	[47][9] = 50,
	[47][12] = 51,
	[48][2] = 9,
	[48][3] = 10,
	[48][4] = 11,
	[48][5] = 12,
	[48][6] = 13,
	[48][7] = 14,
	[50][2] = 17,
};


const unsigned zebu_reduces[54][13] = {
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
	[15][8] = 6,
	[18][8] = 7,
	[20][9] = 6,
	[20][10] = 6,
	[22][9] = 7,
	[22][10] = 7,
	[25][8] = 8,
	[28][8] = 9,
	[30][9] = 8,
	[30][10] = 8,
	[32][9] = 9,
	[32][10] = 9,
	[33][8] = 10,
	[34][9] = 1,
	[34][12] = 1,
	[35][9] = 2,
	[35][12] = 2,
	[36][9] = 3,
	[36][12] = 3,
	[37][9] = 4,
	[37][12] = 4,
	[40][9] = 11,
	[40][12] = 11,
	[41][8] = 12,
	[42][9] = 10,
	[42][10] = 10,
	[43][9] = 12,
	[43][10] = 12,
	[44][9] = 6,
	[44][12] = 6,
	[46][9] = 7,
	[46][12] = 7,
	[49][9] = 8,
	[49][12] = 8,
	[51][9] = 9,
	[51][12] = 9,
	[52][9] = 10,
	[52][12] = 10,
	[53][9] = 12,
	[53][12] = 12,
};


const unsigned zebu_gotos[51][5] = {
	[1][1] = 8,
	[6][1] = 16,
	[6][2] = 15,
	[7][3] = 18,
	[7][4] = 19,
	[13][1] = 21,
	[13][2] = 20,
	[14][3] = 22,
	[14][4] = 23,
	[24][1] = 16,
	[24][2] = 33,
	[26][1] = 40,
	[27][3] = 41,
	[27][4] = 19,
	[29][1] = 21,
	[29][2] = 42,
	[31][3] = 43,
	[31][4] = 23,
	[38][1] = 45,
	[38][2] = 44,
	[39][3] = 46,
	[39][4] = 47,
	[48][1] = 45,
	[48][2] = 52,
	[50][3] = 53,
	[50][4] = 47,
};


struct token
{
unsigned char* data;
unsigned len, refcount;
};
struct __start__
{
	struct value* value;
	unsigned refcount;
};

struct keyvalue
{
	struct token* key;
	struct value* value;
	unsigned refcount;
};

struct value
{
	struct token* boolean;
	struct {
		struct keyvalue** data;
		unsigned n, cap;
	} dict;
	struct {
		struct value** data;
		unsigned n, cap;
	} elements;
	struct token* number;
	struct token* string;
	unsigned refcount;
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
void print___start__(struct link* links, enum prefix p, const char* name, struct __start__* ptree);

void print_keyvalue(struct link* links, enum prefix p, const char* name, struct keyvalue* ptree);

void print_value(struct link* links, enum prefix p, const char* name, struct value* ptree);

void print___start__(struct link* links, enum prefix p, const char* name, struct __start__* ptree)
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
		print_value(new ?: links, p_last_child, "value", ptree->value);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "value");
	free(new);
}
void print_keyvalue(struct link* links, enum prefix p, const char* name, struct keyvalue* ptree)
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
	printf("\e[34m%s\e[m (\e[36mkeyvalue\e[m)\n", name);
	if (ptree->key)
		print_token_leaf(new ?: links, p_not_last_child, "key", ptree->key);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "key");
	if (ptree->value)
		print_value(new ?: links, p_last_child, "value", ptree->value);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "value");
	free(new);
}
void print_value(struct link* links, enum prefix p, const char* name, struct value* ptree)
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
	if (ptree->dict.n)
	{
		for (unsigned i = 0, n = ptree->dict.n; i < n; i++)
		{
			char label[4 + 30];
			snprintf(label, sizeof(label), "dict[%u]", i);
			print_keyvalue(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->dict.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "keyvalue[]", "dict");
	}
	if (ptree->elements.n)
	{
		for (unsigned i = 0, n = ptree->elements.n; i < n; i++)
		{
			char label[8 + 30];
			snprintf(label, sizeof(label), "elements[%u]", i);
			print_value(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->elements.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "value[]", "elements");
	}
	if (ptree->number)
		print_token_leaf(new ?: links, p_not_last_child, "number", ptree->number);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "number");
	if (ptree->string)
		print_token_leaf(new ?: links, p_last_child, "string", ptree->string);
	else
		print_empty_leaf(new ?: links, p_last_child, "token", "string");
	free(new);
}


struct token* inc_token(struct token* this)
{
	if (this) this->refcount++;
	return this;
}
struct __start__* inc___start___tree(struct __start__* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct keyvalue* inc_keyvalue_tree(struct keyvalue* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct value* inc_value_tree(struct value* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}



void free_token(struct token* this)
{
	if (this && !--this->refcount)
	{
		free(this->data);
		free(this);
	}
}
void free___start__(struct __start__* ptree);

void free_keyvalue(struct keyvalue* ptree);

void free_value(struct value* ptree);

void free___start__(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_value(ptree->value);
		free(ptree);
	}
}

void free_keyvalue(struct keyvalue* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_token(ptree->key);
		free_value(ptree->value);
		free(ptree);
	}
}

void free_value(struct value* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_token(ptree->boolean);
		for (unsigned i = 0, n = ptree->dict.n; i < n; i++)
			free_keyvalue(ptree->dict.data[i]);
		free(ptree->dict.data);
		for (unsigned i = 0, n = ptree->elements.n; i < n; i++)
			free_value(ptree->elements.data[i]);
		free(ptree->elements.data);
		free_token(ptree->number);
		free_token(ptree->string);
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
					
					a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
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
					token->refcount = 1;
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
	case 10:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->dict.n)			{
				while (value->dict.n + trie->dict.n > value->dict.cap)
				{
					value->dict.cap = value->dict.cap << 1 ?: 1;
					value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
				}
				memmove(value->dict.data + trie->dict.n, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
				memcpy(value->dict.data, trie->dict.data, sizeof(*trie->dict.data) * trie->dict.n);
				value->dict.n += trie->dict.n;
			}
			if (trie->elements.n)			{
				while (value->elements.n + trie->elements.n > value->elements.cap)
				{
					value->elements.cap = value->elements.cap << 1 ?: 1;
					value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
				}
				memmove(value->elements.data + trie->elements.n, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
				memcpy(value->elements.data, trie->elements.data, sizeof(*trie->elements.data) * trie->elements.n);
				value->elements.n += trie->elements.n;
			}
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		if (value->elements.n == value->elements.cap)
		{
			value->elements.cap = value->elements.cap << 1 ?: 1;
			value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
		}
		memmove(value->elements.data + 1, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
		value->elements.data[0] = data.data[--yacc.n, --data.n], value->elements.n++;
		d = value, g = 2;
		break;
	}
	case 8:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		if (value->elements.n == value->elements.cap)
		{
			value->elements.cap = value->elements.cap << 1 ?: 1;
			value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
		}
		memmove(value->elements.data + 1, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
		value->elements.data[0] = data.data[--yacc.n, --data.n], value->elements.n++;
		d = value, g = 2;
		break;
	}
	case 12:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->dict.n)			{
				while (value->dict.n + trie->dict.n > value->dict.cap)
				{
					value->dict.cap = value->dict.cap << 1 ?: 1;
					value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
				}
				memmove(value->dict.data + trie->dict.n, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
				memcpy(value->dict.data, trie->dict.data, sizeof(*trie->dict.data) * trie->dict.n);
				value->dict.n += trie->dict.n;
			}
			if (trie->elements.n)			{
				while (value->elements.n + trie->elements.n > value->elements.cap)
				{
					value->elements.cap = value->elements.cap << 1 ?: 1;
					value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
				}
				memmove(value->elements.data + trie->elements.n, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
				memcpy(value->elements.data, trie->elements.data, sizeof(*trie->elements.data) * trie->elements.n);
				value->elements.n += trie->elements.n;
			}
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		if (value->dict.n == value->dict.cap)
		{
			value->dict.cap = value->dict.cap << 1 ?: 1;
			value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
		}
		memmove(value->dict.data + 1, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
		value->dict.data[0] = data.data[--yacc.n, --data.n], value->dict.n++;
		d = value, g = 3;
		break;
	}
	case 9:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		if (value->dict.n == value->dict.cap)
		{
			value->dict.cap = value->dict.cap << 1 ?: 1;
			value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
		}
		memmove(value->dict.data + 1, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
		value->dict.data[0] = data.data[--yacc.n, --data.n], value->dict.n++;
		d = value, g = 3;
		break;
	}
	case 5:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_value(value->value), value->value = data.data[--yacc.n, --data.n];
		d = value, g = 5;
		break;
	}
	case 11:
	{
		struct keyvalue* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_value(value->value), value->value = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->key), value->key = data.data[--yacc.n, --data.n];
		d = value, g = 4;
		break;
	}
	case 4:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->number), value->number = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 3:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->boolean), value->boolean = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 7:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->dict.n)			{
				while (value->dict.n + trie->dict.n > value->dict.cap)
				{
					value->dict.cap = value->dict.cap << 1 ?: 1;
					value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
				}
				memmove(value->dict.data + trie->dict.n, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
				memcpy(value->dict.data, trie->dict.data, sizeof(*trie->dict.data) * trie->dict.n);
				value->dict.n += trie->dict.n;
			}
			if (trie->elements.n)			{
				while (value->elements.n + trie->elements.n > value->elements.cap)
				{
					value->elements.cap = value->elements.cap << 1 ?: 1;
					value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
				}
				memmove(value->elements.data + trie->elements.n, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
				memcpy(value->elements.data, trie->elements.data, sizeof(*trie->elements.data) * trie->elements.n);
				value->elements.n += trie->elements.n;
			}
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->string), value->string = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 6:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->boolean) { free_token(value->boolean); value->boolean = trie->boolean; }
			if (trie->dict.n)			{
				while (value->dict.n + trie->dict.n > value->dict.cap)
				{
					value->dict.cap = value->dict.cap << 1 ?: 1;
					value->dict.data = realloc(value->dict.data, sizeof(*value->dict.data) * value->dict.cap);
				}
				memmove(value->dict.data + trie->dict.n, value->dict.data, sizeof(*value->dict.data) * value->dict.n);
				memcpy(value->dict.data, trie->dict.data, sizeof(*trie->dict.data) * trie->dict.n);
				value->dict.n += trie->dict.n;
			}
			if (trie->elements.n)			{
				while (value->elements.n + trie->elements.n > value->elements.cap)
				{
					value->elements.cap = value->elements.cap << 1 ?: 1;
					value->elements.data = realloc(value->elements.data, sizeof(*value->elements.data) * value->elements.cap);
				}
				memmove(value->elements.data + trie->elements.n, value->elements.data, sizeof(*value->elements.data) * value->elements.n);
				memcpy(value->elements.data, trie->elements.data, sizeof(*trie->elements.data) * trie->elements.n);
				value->elements.n += trie->elements.n;
			}
			if (trie->number) { free_token(value->number); value->number = trie->number; }
			if (trie->string) { free_token(value->string); value->string = trie->string; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 2:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->boolean), value->boolean = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
}
				
				if (g == 5)
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
		
		print___start__(NULL, p_root, "start", root);
		
		free___start__(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










