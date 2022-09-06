#include "math.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const unsigned zebu_lexer[10][58] = {
	[1][32] = 1,
	[1][40] = 8,
	[1][48] = 9,
	[1][49] = 9,
	[1][50] = 9,
	[1][51] = 9,
	[1][52] = 9,
	[1][53] = 9,
	[1][54] = 9,
	[1][55] = 9,
	[1][56] = 9,
	[1][57] = 9,
	[2][32] = 2,
	[2][42] = 10,
	[2][43] = 11,
	[2][45] = 12,
	[2][47] = 13,
	[3][32] = 3,
	[4][32] = 4,
	[4][43] = 11,
	[4][45] = 12,
	[5][32] = 5,
	[5][41] = 15,
	[5][42] = 10,
	[5][43] = 11,
	[5][45] = 12,
	[5][47] = 13,
	[6][32] = 6,
	[6][41] = 15,
	[7][32] = 7,
	[7][41] = 15,
	[7][43] = 11,
	[7][45] = 12,
	[9][48] = 9,
	[9][49] = 9,
	[9][50] = 9,
	[9][51] = 9,
	[9][52] = 9,
	[9][53] = 9,
	[9][54] = 9,
	[9][55] = 9,
	[9][56] = 9,
	[9][57] = 9,
};


const unsigned zebu_lexer_starts[45] = {
	[1] = 1,
	[2] = 2,
	[3] = 1,
	[4] = 3,
	[5] = 2,
	[6] = 4,
	[7] = 3,
	[8] = 5,
	[9] = 1,
	[10] = 6,
	[11] = 5,
	[12] = 7,
	[13] = 6,
	[14] = 1,
	[15] = 1,
	[16] = 4,
	[17] = 1,
	[18] = 1,
	[19] = 3,
	[20] = 6,
	[21] = 1,
	[22] = 1,
	[23] = 7,
	[24] = 1,
	[25] = 1,
	[26] = 6,
	[27] = 2,
	[28] = 2,
	[29] = 2,
	[30] = 4,
	[31] = 4,
	[32] = 5,
	[33] = 5,
	[34] = 5,
	[35] = 7,
	[36] = 7,
	[37] = 4,
	[38] = 4,
	[39] = 3,
	[40] = 3,
	[41] = 7,
	[42] = 7,
	[43] = 6,
	[44] = 6,
};


const unsigned zebu_lexer_accepts[16] = {
	[8] = 3,
	[9] = 2,
	[10] = 4,
	[11] = 6,
	[12] = 7,
	[13] = 5,
	[14] = 8,
	[15] = 9,
};


const unsigned zebu_lexer_EOFs[5] = {
	[2] = 14,
	[3] = 14,
	[4] = 14,
};


const unsigned zebu_shifts[37][10] = {
	[1][2] = 2,
	[1][3] = 3,
	[3][2] = 8,
	[3][3] = 9,
	[5][4] = 14,
	[5][5] = 15,
	[6][6] = 17,
	[6][7] = 18,
	[9][2] = 8,
	[9][3] = 9,
	[11][4] = 21,
	[11][5] = 22,
	[12][6] = 24,
	[12][7] = 25,
	[13][9] = 27,
	[14][2] = 2,
	[14][3] = 3,
	[15][2] = 2,
	[15][3] = 3,
	[17][2] = 2,
	[17][3] = 3,
	[18][2] = 2,
	[18][3] = 3,
	[20][9] = 32,
	[21][2] = 8,
	[21][3] = 9,
	[22][2] = 8,
	[22][3] = 9,
	[24][2] = 8,
	[24][3] = 9,
	[25][2] = 8,
	[25][3] = 9,
	[28][4] = 14,
	[28][5] = 15,
	[29][4] = 14,
	[29][5] = 15,
	[30][6] = 17,
	[30][7] = 18,
	[31][6] = 17,
	[31][7] = 18,
	[33][4] = 21,
	[33][5] = 22,
	[34][4] = 21,
	[34][5] = 22,
	[35][6] = 24,
	[35][7] = 25,
	[36][6] = 24,
	[36][7] = 25,
};


const unsigned zebu_reduces[45][10] = {
	[2][4] = 1,
	[2][5] = 1,
	[2][6] = 1,
	[2][7] = 1,
	[2][8] = 1,
	[4][8] = 2,
	[5][6] = 3,
	[5][7] = 3,
	[5][8] = 3,
	[6][8] = 4,
	[7][8] = 5,
	[8][4] = 1,
	[8][5] = 1,
	[8][6] = 1,
	[8][7] = 1,
	[8][9] = 1,
	[10][9] = 2,
	[11][6] = 3,
	[11][7] = 3,
	[11][9] = 3,
	[12][9] = 4,
	[16][6] = 6,
	[16][7] = 6,
	[16][8] = 6,
	[19][8] = 7,
	[23][6] = 6,
	[23][7] = 6,
	[23][9] = 6,
	[26][9] = 7,
	[27][4] = 8,
	[27][5] = 8,
	[27][6] = 8,
	[27][7] = 8,
	[27][8] = 8,
	[28][6] = 9,
	[28][7] = 9,
	[28][8] = 9,
	[29][6] = 10,
	[29][7] = 10,
	[29][8] = 10,
	[30][8] = 11,
	[31][8] = 12,
	[32][4] = 8,
	[32][5] = 8,
	[32][6] = 8,
	[32][7] = 8,
	[32][9] = 8,
	[33][6] = 9,
	[33][7] = 9,
	[33][9] = 9,
	[34][6] = 10,
	[34][7] = 10,
	[34][9] = 10,
	[35][9] = 11,
	[36][9] = 12,
	[37][6] = 13,
	[37][7] = 13,
	[37][8] = 13,
	[38][6] = 14,
	[38][7] = 14,
	[38][8] = 14,
	[39][8] = 15,
	[40][8] = 16,
	[41][6] = 13,
	[41][7] = 13,
	[41][9] = 13,
	[42][6] = 14,
	[42][7] = 14,
	[42][9] = 14,
	[43][9] = 15,
	[44][9] = 16,
};


const unsigned zebu_gotos[37][7] = {
	[1][1] = 4,
	[1][2] = 5,
	[1][3] = 6,
	[1][4] = 7,
	[3][1] = 10,
	[3][2] = 11,
	[3][3] = 12,
	[3][4] = 13,
	[5][5] = 16,
	[6][6] = 19,
	[9][1] = 10,
	[9][2] = 11,
	[9][3] = 12,
	[9][4] = 20,
	[11][5] = 23,
	[12][6] = 26,
	[14][2] = 28,
	[15][2] = 29,
	[17][2] = 5,
	[17][3] = 30,
	[18][2] = 5,
	[18][3] = 31,
	[21][2] = 33,
	[22][2] = 34,
	[24][2] = 11,
	[24][3] = 35,
	[25][2] = 11,
	[25][3] = 36,
	[28][5] = 37,
	[29][5] = 38,
	[30][6] = 39,
	[31][6] = 40,
	[33][5] = 41,
	[34][5] = 42,
	[35][6] = 43,
	[36][6] = 44,
};


struct token
{
unsigned char* data;
unsigned len, refcount;
};
struct __start__
{
	struct root* root;
	unsigned refcount;
};

struct addition
{
	struct {
		struct multiply** data;
		unsigned n, cap;
	} addmes;
	struct multiply* base;
	struct {
		struct multiply** data;
		unsigned n, cap;
	} subtractmes;
	unsigned refcount;
};

struct highest
{
	struct token* literal;
	struct root* subexpression;
	unsigned refcount;
};

struct multiply
{
	struct highest* base;
	struct {
		struct highest** data;
		unsigned n, cap;
	} dividemes;
	struct {
		struct highest** data;
		unsigned n, cap;
	} multiplymes;
	unsigned refcount;
};

struct root
{
	struct addition* root;
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

void print_addition(struct link* links, enum prefix p, const char* name, struct addition* ptree);

void print_highest(struct link* links, enum prefix p, const char* name, struct highest* ptree);

void print_multiply(struct link* links, enum prefix p, const char* name, struct multiply* ptree);

void print_root(struct link* links, enum prefix p, const char* name, struct root* ptree);

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
	if (ptree->root)
		print_root(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "root");
	free(new);
}
void print_addition(struct link* links, enum prefix p, const char* name, struct addition* ptree)
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
	printf("\e[34m%s\e[m (\e[36maddition\e[m)\n", name);
	if (ptree->addmes.n)
	{
		for (unsigned i = 0, n = ptree->addmes.n; i < n; i++)
		{
			char label[6 + 30];
			snprintf(label, sizeof(label), "addmes[%u]", i);
			print_multiply(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->addmes.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "multiply[]", "addmes");
	}
	if (ptree->base)
		print_multiply(new ?: links, p_not_last_child, "base", ptree->base);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "multiply", "base");
	if (ptree->subtractmes.n)
	{
		for (unsigned i = 0, n = ptree->subtractmes.n; i < n; i++)
		{
			char label[11 + 30];
			snprintf(label, sizeof(label), "subtractmes[%u]", i);
			print_multiply(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->subtractmes.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_last_child, "multiply[]", "subtractmes");
	}
	free(new);
}
void print_highest(struct link* links, enum prefix p, const char* name, struct highest* ptree)
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
	printf("\e[34m%s\e[m (\e[36mhighest\e[m)\n", name);
	if (ptree->literal)
		print_token_leaf(new ?: links, p_not_last_child, "literal", ptree->literal);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "literal");
	if (ptree->subexpression)
		print_root(new ?: links, p_last_child, "subexpression", ptree->subexpression);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "subexpression");
	free(new);
}
void print_multiply(struct link* links, enum prefix p, const char* name, struct multiply* ptree)
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
	printf("\e[34m%s\e[m (\e[36mmultiply\e[m)\n", name);
	if (ptree->base)
		print_highest(new ?: links, p_not_last_child, "base", ptree->base);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "highest", "base");
	if (ptree->dividemes.n)
	{
		for (unsigned i = 0, n = ptree->dividemes.n; i < n; i++)
		{
			char label[9 + 30];
			snprintf(label, sizeof(label), "dividemes[%u]", i);
			print_highest(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->dividemes.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "highest[]", "dividemes");
	}
	if (ptree->multiplymes.n)
	{
		for (unsigned i = 0, n = ptree->multiplymes.n; i < n; i++)
		{
			char label[11 + 30];
			snprintf(label, sizeof(label), "multiplymes[%u]", i);
			print_highest(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->multiplymes.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_last_child, "highest[]", "multiplymes");
	}
	free(new);
}
void print_root(struct link* links, enum prefix p, const char* name, struct root* ptree)
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
	printf("\e[34m%s\e[m (\e[36mroot\e[m)\n", name);
	if (ptree->root)
		print_addition(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "addition", "root");
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

struct addition* inc_addition_tree(struct addition* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct highest* inc_highest_tree(struct highest* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct multiply* inc_multiply_tree(struct multiply* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct root* inc_root_tree(struct root* ptree)
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

void free_addition(struct addition* ptree);

void free_highest(struct highest* ptree);

void free_multiply(struct multiply* ptree);

void free_root(struct root* ptree);

void free___start__(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_root(ptree->root);
		free(ptree);
	}
}

void free_addition(struct addition* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->addmes.n; i < n; i++)
			free_multiply(ptree->addmes.data[i]);
		free(ptree->addmes.data);
		free_multiply(ptree->base);
		for (unsigned i = 0, n = ptree->subtractmes.n; i < n; i++)
			free_multiply(ptree->subtractmes.data[i]);
		free(ptree->subtractmes.data);
		free(ptree);
	}
}

void free_highest(struct highest* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_token(ptree->literal);
		free_root(ptree->subexpression);
		free(ptree);
	}
}

void free_multiply(struct multiply* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_highest(ptree->base);
		for (unsigned i = 0, n = ptree->dividemes.n; i < n; i++)
			free_highest(ptree->dividemes.data[i]);
		free(ptree->dividemes.data);
		for (unsigned i = 0, n = ptree->multiplymes.n; i < n; i++)
			free_highest(ptree->multiplymes.data[i]);
		free(ptree->multiplymes.data);
		free(ptree);
	}
}

void free_root(struct root* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_addition(ptree->root);
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
	case 12:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->subtractmes.n == value->subtractmes.cap)
		{
			value->subtractmes.cap = value->subtractmes.cap << 1 ?: 1;
			value->subtractmes.data = realloc(value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.cap);
		}
		memmove(value->subtractmes.data + 1, value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.n);
		value->subtractmes.data[0] = data.data[--yacc.n, --data.n], value->subtractmes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 15:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct addition* trie = data.data[--yacc.n, --data.n];
			if (trie->addmes.n)			{
				while (value->addmes.n + trie->addmes.n > value->addmes.cap)
				{
					value->addmes.cap = value->addmes.cap << 1 ?: 1;
					value->addmes.data = realloc(value->addmes.data, sizeof(*value->addmes.data) * value->addmes.cap);
				}
				memmove(value->addmes.data + trie->addmes.n, value->addmes.data, sizeof(*value->addmes.data) * value->addmes.n);
				memcpy(value->addmes.data, trie->addmes.data, sizeof(*trie->addmes.data) * trie->addmes.n);
				value->addmes.n += trie->addmes.n;
			}
			if (trie->base) { free_multiply(value->base); value->base = trie->base; }
			if (trie->subtractmes.n)			{
				while (value->subtractmes.n + trie->subtractmes.n > value->subtractmes.cap)
				{
					value->subtractmes.cap = value->subtractmes.cap << 1 ?: 1;
					value->subtractmes.data = realloc(value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.cap);
				}
				memmove(value->subtractmes.data + trie->subtractmes.n, value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.n);
				memcpy(value->subtractmes.data, trie->subtractmes.data, sizeof(*trie->subtractmes.data) * trie->subtractmes.n);
				value->subtractmes.n += trie->subtractmes.n;
			}
			free(trie);
		};
		if (value->addmes.n == value->addmes.cap)
		{
			value->addmes.cap = value->addmes.cap << 1 ?: 1;
			value->addmes.data = realloc(value->addmes.data, sizeof(*value->addmes.data) * value->addmes.cap);
		}
		memmove(value->addmes.data + 1, value->addmes.data, sizeof(*value->addmes.data) * value->addmes.n);
		value->addmes.data[0] = data.data[--yacc.n, --data.n], value->addmes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 16:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct addition* trie = data.data[--yacc.n, --data.n];
			if (trie->addmes.n)			{
				while (value->addmes.n + trie->addmes.n > value->addmes.cap)
				{
					value->addmes.cap = value->addmes.cap << 1 ?: 1;
					value->addmes.data = realloc(value->addmes.data, sizeof(*value->addmes.data) * value->addmes.cap);
				}
				memmove(value->addmes.data + trie->addmes.n, value->addmes.data, sizeof(*value->addmes.data) * value->addmes.n);
				memcpy(value->addmes.data, trie->addmes.data, sizeof(*trie->addmes.data) * trie->addmes.n);
				value->addmes.n += trie->addmes.n;
			}
			if (trie->base) { free_multiply(value->base); value->base = trie->base; }
			if (trie->subtractmes.n)			{
				while (value->subtractmes.n + trie->subtractmes.n > value->subtractmes.cap)
				{
					value->subtractmes.cap = value->subtractmes.cap << 1 ?: 1;
					value->subtractmes.data = realloc(value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.cap);
				}
				memmove(value->subtractmes.data + trie->subtractmes.n, value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.n);
				memcpy(value->subtractmes.data, trie->subtractmes.data, sizeof(*trie->subtractmes.data) * trie->subtractmes.n);
				value->subtractmes.n += trie->subtractmes.n;
			}
			free(trie);
		};
		if (value->subtractmes.n == value->subtractmes.cap)
		{
			value->subtractmes.cap = value->subtractmes.cap << 1 ?: 1;
			value->subtractmes.data = realloc(value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.cap);
		}
		memmove(value->subtractmes.data + 1, value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.n);
		value->subtractmes.data[0] = data.data[--yacc.n, --data.n], value->subtractmes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 11:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->addmes.n == value->addmes.cap)
		{
			value->addmes.cap = value->addmes.cap << 1 ?: 1;
			value->addmes.data = realloc(value->addmes.data, sizeof(*value->addmes.data) * value->addmes.cap);
		}
		memmove(value->addmes.data + 1, value->addmes.data, sizeof(*value->addmes.data) * value->addmes.n);
		value->addmes.data[0] = data.data[--yacc.n, --data.n], value->addmes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 9:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->multiplymes.n == value->multiplymes.cap)
		{
			value->multiplymes.cap = value->multiplymes.cap << 1 ?: 1;
			value->multiplymes.data = realloc(value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.cap);
		}
		memmove(value->multiplymes.data + 1, value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.n);
		value->multiplymes.data[0] = data.data[--yacc.n, --data.n], value->multiplymes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 13:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct multiply* trie = data.data[--yacc.n, --data.n];
			if (trie->base) { free_highest(value->base); value->base = trie->base; }
			if (trie->dividemes.n)			{
				while (value->dividemes.n + trie->dividemes.n > value->dividemes.cap)
				{
					value->dividemes.cap = value->dividemes.cap << 1 ?: 1;
					value->dividemes.data = realloc(value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.cap);
				}
				memmove(value->dividemes.data + trie->dividemes.n, value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.n);
				memcpy(value->dividemes.data, trie->dividemes.data, sizeof(*trie->dividemes.data) * trie->dividemes.n);
				value->dividemes.n += trie->dividemes.n;
			}
			if (trie->multiplymes.n)			{
				while (value->multiplymes.n + trie->multiplymes.n > value->multiplymes.cap)
				{
					value->multiplymes.cap = value->multiplymes.cap << 1 ?: 1;
					value->multiplymes.data = realloc(value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.cap);
				}
				memmove(value->multiplymes.data + trie->multiplymes.n, value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.n);
				memcpy(value->multiplymes.data, trie->multiplymes.data, sizeof(*trie->multiplymes.data) * trie->multiplymes.n);
				value->multiplymes.n += trie->multiplymes.n;
			}
			free(trie);
		};
		if (value->multiplymes.n == value->multiplymes.cap)
		{
			value->multiplymes.cap = value->multiplymes.cap << 1 ?: 1;
			value->multiplymes.data = realloc(value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.cap);
		}
		memmove(value->multiplymes.data + 1, value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.n);
		value->multiplymes.data[0] = data.data[--yacc.n, --data.n], value->multiplymes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 10:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->dividemes.n == value->dividemes.cap)
		{
			value->dividemes.cap = value->dividemes.cap << 1 ?: 1;
			value->dividemes.data = realloc(value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.cap);
		}
		memmove(value->dividemes.data + 1, value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.n);
		value->dividemes.data[0] = data.data[--yacc.n, --data.n], value->dividemes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 14:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct multiply* trie = data.data[--yacc.n, --data.n];
			if (trie->base) { free_highest(value->base); value->base = trie->base; }
			if (trie->dividemes.n)			{
				while (value->dividemes.n + trie->dividemes.n > value->dividemes.cap)
				{
					value->dividemes.cap = value->dividemes.cap << 1 ?: 1;
					value->dividemes.data = realloc(value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.cap);
				}
				memmove(value->dividemes.data + trie->dividemes.n, value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.n);
				memcpy(value->dividemes.data, trie->dividemes.data, sizeof(*trie->dividemes.data) * trie->dividemes.n);
				value->dividemes.n += trie->dividemes.n;
			}
			if (trie->multiplymes.n)			{
				while (value->multiplymes.n + trie->multiplymes.n > value->multiplymes.cap)
				{
					value->multiplymes.cap = value->multiplymes.cap << 1 ?: 1;
					value->multiplymes.data = realloc(value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.cap);
				}
				memmove(value->multiplymes.data + trie->multiplymes.n, value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.n);
				memcpy(value->multiplymes.data, trie->multiplymes.data, sizeof(*trie->multiplymes.data) * trie->multiplymes.n);
				value->multiplymes.n += trie->multiplymes.n;
			}
			free(trie);
		};
		if (value->dividemes.n == value->dividemes.cap)
		{
			value->dividemes.cap = value->dividemes.cap << 1 ?: 1;
			value->dividemes.data = realloc(value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.cap);
		}
		memmove(value->dividemes.data + 1, value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.n);
		value->dividemes.data[0] = data.data[--yacc.n, --data.n], value->dividemes.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 5:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_root(value->root), value->root = data.data[--yacc.n, --data.n];
		d = value, g = 7;
		break;
	}
	case 4:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_multiply(value->base), value->base = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 7:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct addition* trie = data.data[--yacc.n, --data.n];
			if (trie->addmes.n)			{
				while (value->addmes.n + trie->addmes.n > value->addmes.cap)
				{
					value->addmes.cap = value->addmes.cap << 1 ?: 1;
					value->addmes.data = realloc(value->addmes.data, sizeof(*value->addmes.data) * value->addmes.cap);
				}
				memmove(value->addmes.data + trie->addmes.n, value->addmes.data, sizeof(*value->addmes.data) * value->addmes.n);
				memcpy(value->addmes.data, trie->addmes.data, sizeof(*trie->addmes.data) * trie->addmes.n);
				value->addmes.n += trie->addmes.n;
			}
			if (trie->base) { free_multiply(value->base); value->base = trie->base; }
			if (trie->subtractmes.n)			{
				while (value->subtractmes.n + trie->subtractmes.n > value->subtractmes.cap)
				{
					value->subtractmes.cap = value->subtractmes.cap << 1 ?: 1;
					value->subtractmes.data = realloc(value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.cap);
				}
				memmove(value->subtractmes.data + trie->subtractmes.n, value->subtractmes.data, sizeof(*value->subtractmes.data) * value->subtractmes.n);
				memcpy(value->subtractmes.data, trie->subtractmes.data, sizeof(*trie->subtractmes.data) * trie->subtractmes.n);
				value->subtractmes.n += trie->subtractmes.n;
			}
			free(trie);
		};
		free_multiply(value->base), value->base = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->literal), value->literal = data.data[--yacc.n, --data.n];
		d = value, g = 2;
		break;
	}
	case 8:
	{
		struct highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_root(value->subexpression), value->subexpression = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 3:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_highest(value->base), value->base = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 6:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct multiply* trie = data.data[--yacc.n, --data.n];
			if (trie->base) { free_highest(value->base); value->base = trie->base; }
			if (trie->dividemes.n)			{
				while (value->dividemes.n + trie->dividemes.n > value->dividemes.cap)
				{
					value->dividemes.cap = value->dividemes.cap << 1 ?: 1;
					value->dividemes.data = realloc(value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.cap);
				}
				memmove(value->dividemes.data + trie->dividemes.n, value->dividemes.data, sizeof(*value->dividemes.data) * value->dividemes.n);
				memcpy(value->dividemes.data, trie->dividemes.data, sizeof(*trie->dividemes.data) * trie->dividemes.n);
				value->dividemes.n += trie->dividemes.n;
			}
			if (trie->multiplymes.n)			{
				while (value->multiplymes.n + trie->multiplymes.n > value->multiplymes.cap)
				{
					value->multiplymes.cap = value->multiplymes.cap << 1 ?: 1;
					value->multiplymes.data = realloc(value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.cap);
				}
				memmove(value->multiplymes.data + trie->multiplymes.n, value->multiplymes.data, sizeof(*value->multiplymes.data) * value->multiplymes.n);
				memcpy(value->multiplymes.data, trie->multiplymes.data, sizeof(*trie->multiplymes.data) * trie->multiplymes.n);
				value->multiplymes.n += trie->multiplymes.n;
			}
			free(trie);
		};
		free_highest(value->base), value->base = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 2:
	{
		struct root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_addition(value->root), value->root = data.data[--yacc.n, --data.n];
		d = value, g = 4;
		break;
	}
}
				
				if (g == 7)
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










