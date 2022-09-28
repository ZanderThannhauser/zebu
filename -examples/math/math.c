#include "math.h"

#define _GNU_SOURCE

#include <readline/readline.h>
#include <readline/history.h>

#include <errno.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const unsigned zebu_shifts[23][10] = {
	[1][2] = 2,
	[1][3] = 3,
	[3][2] = 8,
	[3][3] = 9,
	[5][4] = 14,
	[5][5] = 15,
	[6][6] = 16,
	[6][7] = 17,
	[9][2] = 8,
	[9][3] = 9,
	[11][4] = 19,
	[11][5] = 20,
	[12][6] = 21,
	[12][7] = 22,
	[13][9] = 23,
	[14][2] = 2,
	[14][3] = 3,
	[15][2] = 2,
	[15][3] = 3,
	[16][2] = 2,
	[16][3] = 3,
	[17][2] = 2,
	[17][3] = 3,
	[18][9] = 30,
	[19][2] = 8,
	[19][3] = 9,
	[20][2] = 8,
	[20][3] = 9,
	[21][2] = 8,
	[21][3] = 9,
	[22][2] = 8,
	[22][3] = 9,
};


const unsigned zebu_reduces[37][10] = {
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
	[23][4] = 6,
	[23][5] = 6,
	[23][6] = 6,
	[23][7] = 6,
	[23][8] = 6,
	[24][6] = 7,
	[24][7] = 7,
	[24][8] = 7,
	[25][6] = 8,
	[25][7] = 8,
	[25][8] = 8,
	[26][6] = 9,
	[26][7] = 9,
	[26][8] = 9,
	[27][8] = 10,
	[28][8] = 11,
	[29][8] = 12,
	[30][4] = 6,
	[30][5] = 6,
	[30][6] = 6,
	[30][7] = 6,
	[30][9] = 6,
	[31][6] = 7,
	[31][7] = 7,
	[31][9] = 7,
	[32][6] = 8,
	[32][7] = 8,
	[32][9] = 8,
	[33][6] = 9,
	[33][7] = 9,
	[33][9] = 9,
	[34][9] = 10,
	[35][9] = 11,
	[36][9] = 12,
};


const unsigned zebu_gotos[23][7] = {
	[1][1] = 4,
	[1][2] = 5,
	[1][3] = 6,
	[1][4] = 7,
	[3][1] = 10,
	[3][2] = 11,
	[3][3] = 12,
	[3][4] = 13,
	[9][1] = 10,
	[9][2] = 11,
	[9][3] = 12,
	[9][4] = 18,
	[14][2] = 5,
	[14][3] = 25,
	[14][5] = 24,
	[15][2] = 5,
	[15][3] = 25,
	[15][5] = 26,
	[16][1] = 28,
	[16][2] = 5,
	[16][3] = 6,
	[16][6] = 27,
	[17][1] = 28,
	[17][2] = 5,
	[17][3] = 6,
	[17][6] = 29,
	[19][2] = 11,
	[19][3] = 32,
	[19][5] = 31,
	[20][2] = 11,
	[20][3] = 32,
	[20][5] = 33,
	[21][1] = 35,
	[21][2] = 11,
	[21][3] = 12,
	[21][6] = 34,
	[22][1] = 35,
	[22][2] = 11,
	[22][3] = 12,
	[22][6] = 36,
};


const unsigned zebu_lexer[32][58] = {
	[1][32] = 8,
	[1][40] = 9,
	[1][48] = 10,
	[1][49] = 10,
	[1][50] = 10,
	[1][51] = 10,
	[1][52] = 10,
	[1][53] = 10,
	[1][54] = 10,
	[1][55] = 10,
	[1][56] = 10,
	[1][57] = 10,
	[2][32] = 11,
	[2][42] = 12,
	[2][43] = 13,
	[2][45] = 14,
	[2][47] = 15,
	[3][32] = 17,
	[4][32] = 19,
	[4][43] = 20,
	[4][45] = 21,
	[5][32] = 23,
	[5][41] = 24,
	[5][42] = 25,
	[5][43] = 26,
	[5][45] = 27,
	[5][47] = 28,
	[6][32] = 29,
	[6][41] = 30,
	[7][32] = 31,
	[7][41] = 32,
	[7][43] = 33,
	[7][45] = 34,
	[8][32] = 8,
	[10][48] = 10,
	[10][49] = 10,
	[10][50] = 10,
	[10][51] = 10,
	[10][52] = 10,
	[10][53] = 10,
	[10][54] = 10,
	[10][55] = 10,
	[10][56] = 10,
	[10][57] = 10,
	[11][32] = 11,
	[17][32] = 17,
	[19][32] = 19,
	[23][32] = 23,
	[29][32] = 29,
	[31][32] = 31,
};


const unsigned zebu_lexer_starts[37] = {
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
	[16] = 1,
	[17] = 1,
	[18] = 6,
	[19] = 1,
	[20] = 1,
	[21] = 1,
	[22] = 1,
	[23] = 2,
	[24] = 4,
	[25] = 4,
	[26] = 4,
	[27] = 3,
	[28] = 3,
	[29] = 3,
	[30] = 5,
	[31] = 7,
	[32] = 7,
	[33] = 7,
	[34] = 6,
	[35] = 6,
	[36] = 6,
};


const unsigned zebu_lexer_accepts[35] = {
	[8] = 1,
	[9] = 3,
	[10] = 2,
	[11] = 1,
	[12] = 4,
	[13] = 6,
	[14] = 7,
	[15] = 5,
	[16] = 8,
	[17] = 1,
	[18] = 8,
	[19] = 1,
	[20] = 6,
	[21] = 7,
	[22] = 8,
	[23] = 1,
	[24] = 9,
	[25] = 4,
	[26] = 6,
	[27] = 7,
	[28] = 5,
	[29] = 1,
	[30] = 9,
	[31] = 1,
	[32] = 9,
	[33] = 6,
	[34] = 7,
};


const unsigned zebu_lexer_EOFs[5] = {
	[2] = 16,
	[3] = 18,
	[4] = 22,
};


struct zebu_token
{
	unsigned char* data;
	unsigned len, refcount;
};

struct zebu_$start
{
	struct zebu_root* root;
	unsigned refcount;
};

struct zebu_addition
{
	struct zebu_addition* add;
	struct zebu_multiply* left;
	unsigned refcount;
};

struct zebu_highest
{
	struct zebu_token* literal;
	struct zebu_root* subexpression;
	unsigned refcount;
};

struct zebu_multiply
{
	struct zebu_highest* left;
	struct zebu_multiply* times;
	unsigned refcount;
};

struct zebu_root
{
	struct zebu_addition* root;
	unsigned refcount;
};



#include <stdbool.h>

struct link
{
	bool is_last;
	struct link* prev;
};

static void print_links(struct link* link)
{
	if (!link) return;
	
	print_links(link->prev);
	
	if (link->is_last)
		fputs("    ", stdout);
	else
		fputs("│   ", stdout);
}

static void print_tree_escape(char *out, char in)
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
		case '`':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\'': *out++ = '\\', *out++ = '\'', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}

enum prefix
{
	p_root,
	p_not_last_child,
	p_last_child,
};

void print_token_leaf(struct link* links, enum prefix p, const char* name, struct zebu_token* token)
{
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[32m%s\e[0m (\e[35m\"", name);
	char escape[10];
	for (unsigned i = 0, n = token->len; i < n; i++)
		print_tree_escape(escape, token->data[i]), fputs(escape, stdout);
	printf("\"\e[0m)\n");
}

void print_scanf_leaf(struct link* links, enum prefix p, const char* name, const char* format, ...)
{
	va_list ap;
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[32m%s\e[0m (\e[35m%s\e[m: \e[35m", name, format);
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	printf("\e[0m)\n");
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
void print_zebu_$start(struct link* links, enum prefix p, const char* name, struct zebu_$start* ptree);

void print_zebu_addition(struct link* links, enum prefix p, const char* name, struct zebu_addition* ptree);

void print_zebu_highest(struct link* links, enum prefix p, const char* name, struct zebu_highest* ptree);

void print_zebu_multiply(struct link* links, enum prefix p, const char* name, struct zebu_multiply* ptree);

void print_zebu_root(struct link* links, enum prefix p, const char* name, struct zebu_root* ptree);

void print_zebu_$start(struct link* links, enum prefix p, const char* name, struct zebu_$start* ptree)
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
	printf("\e[34m%s\e[m (\e[36m$start\e[m)\n", name);
	if (ptree->root)
		print_zebu_root(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "root");
	free(new);
}
void print_zebu_addition(struct link* links, enum prefix p, const char* name, struct zebu_addition* ptree)
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
	if (ptree->add)
		print_zebu_addition(new ?: links, p_not_last_child, "add", ptree->add);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "addition", "add");
	if (ptree->left)
		print_zebu_multiply(new ?: links, p_last_child, "left", ptree->left);
	else
		print_empty_leaf(new ?: links, p_last_child, "multiply", "left");
	free(new);
}
void print_zebu_highest(struct link* links, enum prefix p, const char* name, struct zebu_highest* ptree)
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
		print_zebu_root(new ?: links, p_last_child, "subexpression", ptree->subexpression);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "subexpression");
	free(new);
}
void print_zebu_multiply(struct link* links, enum prefix p, const char* name, struct zebu_multiply* ptree)
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
	if (ptree->left)
		print_zebu_highest(new ?: links, p_not_last_child, "left", ptree->left);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "highest", "left");
	if (ptree->times)
		print_zebu_multiply(new ?: links, p_last_child, "times", ptree->times);
	else
		print_empty_leaf(new ?: links, p_last_child, "multiply", "times");
	free(new);
}
void print_zebu_root(struct link* links, enum prefix p, const char* name, struct zebu_root* ptree)
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
		print_zebu_addition(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "addition", "root");
	free(new);
}


struct zebu_token* inc_zebu_token(struct zebu_token* this)
{
	if (this) this->refcount++;
	return this;
}
struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_addition* inc_zebu_addition(struct zebu_addition* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_highest* inc_zebu_highest(struct zebu_highest* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_multiply* inc_zebu_multiply(struct zebu_multiply* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct zebu_root* inc_zebu_root(struct zebu_root* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}



extern void free_zebu_token(struct zebu_token* this);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_addition(struct zebu_addition* ptree);

extern void free_zebu_highest(struct zebu_highest* ptree);

extern void free_zebu_multiply(struct zebu_multiply* ptree);

extern void free_zebu_root(struct zebu_root* ptree);

void free_zebu_token(struct zebu_token* this)
{
	if (this && !--this->refcount)
	{
		free(this->data);
		free(this);
	}
}
void free_zebu_$start(struct zebu_$start* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_root(ptree->root);
		free(ptree);
	}
}

void free_zebu_addition(struct zebu_addition* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_addition(ptree->add);
		free_zebu_multiply(ptree->left);
		free(ptree);
	}
}

void free_zebu_highest(struct zebu_highest* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_token(ptree->literal);
		free_zebu_root(ptree->subexpression);
		free(ptree);
	}
}

void free_zebu_multiply(struct zebu_multiply* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_highest(ptree->left);
		free_zebu_multiply(ptree->times);
		free(ptree);
	}
}

void free_zebu_root(struct zebu_root* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_zebu_addition(ptree->root);
		free(ptree);
	}
}



#ifdef ZEBU_DEBUG
static const char* zebu_token_names[11] = {
	[2] = "2",
	[3] = "3",
	[9] = "4",
	[4] = "5",
	[5] = "6",
	[6] = "7",
	[7] = "8",
	[8] = "9",
};

#endif

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef ZEBU_DEBUG
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
			sprintf(out, "\\x%02hhX", in);
			break;
	}
}
#endif

int main(int argc, char** argv)
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	#ifdef ZEBU_DEBUG
	setvbuf(stdout, 0, _IONBF, 0);
	#endif
	
	#ifdef ZEBU_DEBUG
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
	#endif
	
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
			#ifdef ZEBU_DEBUG
			char escaped[10];
			#endif
			
			unsigned original_l = l;
			
			char* begin = lexer, *f = NULL;
			
			unsigned a, b;
			unsigned char c;
			
			while (1)
			{
				if ((c = *lexer))
				{
					#ifdef ZEBU_DEBUG
					escape(escaped, c);
					
					ddprintf("lexer: c = '%s' (0x%X)\n", escaped, c);
					#endif
					
					a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
				}
				else
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: c == <EOF>\n");
					#endif
					
					// it would be cool if it would read another line
					// if there wasn't an EOF transition
					a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
				}
				
				b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
				
				#ifdef ZEBU_DEBUG
				ddprintf("lexer: l = %u, a = %u, b = %u\n", l, a, b);
				#endif
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = lexer++;
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: l = %u, t == %u, f = %p (saved)\n", l, t, f);
						#endif
					}
					else
					{
						l = a;
						if (c) lexer++;
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: l == %u\n", l);
						#endif
					}
				}
				else if (b)
				{
					#ifdef ZEBU_DEBUG
					ddprintf("lexer: \"%.*s\"\n", lexer - begin, begin);
					#endif
					
					if (b == 1)
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: whitespace: \"%.*s\"\n", lexer - begin, begin);
						#endif
						l = original_l, begin = lexer, f = NULL;
					}
					else
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: token: \"%.*s\"\n", lexer - begin, begin);
						#endif
						struct zebu_token* token = malloc(sizeof(*token));
						token->refcount = 1;
						token->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);
						token->len = lexer - begin;
						token->data[token->len] = '\0';
						t = b, td = token;
						break;
					}
				}
				else if (f)
				{
					if (t == 1)
					{
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: falling back to whitespace: \"%.*s\"\n", lexer - begin, begin);
						#endif
						
						assert(!"TODO");
					}
					else
					{
						lexer = f;
						
						#ifdef ZEBU_DEBUG
						ddprintf("lexer: falling back to token: \"%.*s\"\n", lexer - begin, begin);
						#endif
						
						struct zebu_token* token = malloc(sizeof(*token));
						token->refcount = 1;
						token->data = memcpy(malloc(lexer - begin + 1), begin, lexer - begin);
						token->len = lexer - begin;
						token->data[token->len] = '\0';
						td = token;
						break;
					}
				}
				else
				{
					assert(!"TODO");
				}
			}
		}
		
		yacc.n = 0, data.n = 0, y = 1, push_state(y);
		
		read_token(zebu_lexer_starts[y]);
		
		#ifdef ZEBU_DEBUG
		ddprintf("y = %u, t == %u (%s)\n", y, t, zebu_token_names[t]);
		#endif
		
		void* root;
		
		while (yacc.n)
		{
			if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
			{
				y = s, push_state(y), push_data(td);
				
				read_token(zebu_lexer_starts[y]);
				
				#ifdef ZEBU_DEBUG
				ddprintf("t == %u (%s)\n", t, zebu_token_names[t]);
				#endif
			}
			else if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
			{
				unsigned g;
				
				void* d;
				
				#ifdef ZEBU_DEBUG
				ddprintf("r = %u\n", r);
				#endif
				
				switch (r)
{
	case 5:
	{
		struct zebu_$start* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_root* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_root(value->root), value->root = inc_zebu_root(subgrammar);
		free_zebu_root(subgrammar);
		}
		d = value, g = 7;
		break;
	}
	case 11:
	{
		struct zebu_addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_addition* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_addition(value->add), value->add = inc_zebu_addition(subgrammar);
		free_zebu_addition(subgrammar);
		}
		d = value, g = 6;
		break;
	}
	case 8:
	{
		struct zebu_multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_multiply* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_multiply(value->times), value->times = inc_zebu_multiply(subgrammar);
		free_zebu_multiply(subgrammar);
		}
		d = value, g = 5;
		break;
	}
	case 4:
	{
		struct zebu_addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_multiply* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_multiply(value->left), value->left = inc_zebu_multiply(subgrammar);
		free_zebu_multiply(subgrammar);
		}
		d = value, g = 1;
		break;
	}
	case 10:
	{
		struct zebu_addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct zebu_addition* trie = data.data[--yacc.n, --data.n];
			if (trie->add) { free_zebu_addition(value->add); value->add = inc_zebu_addition(trie->add); }
			if (trie->left) { free_zebu_multiply(value->left); value->left = inc_zebu_multiply(trie->left); }
			free_zebu_addition(trie);
		}
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		{
		struct zebu_multiply* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_multiply(value->left), value->left = inc_zebu_multiply(subgrammar);
		free_zebu_multiply(subgrammar);
		}
		d = value, g = 1;
		break;
	}
	case 12:
	{
		struct zebu_addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct zebu_addition* trie = data.data[--yacc.n, --data.n];
			if (trie->add) { free_zebu_addition(value->add); value->add = inc_zebu_addition(trie->add); }
			if (trie->left) { free_zebu_multiply(value->left); value->left = inc_zebu_multiply(trie->left); }
			free_zebu_addition(trie);
		}
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		{
		struct zebu_multiply* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_multiply(value->left), value->left = inc_zebu_multiply(subgrammar);
		free_zebu_multiply(subgrammar);
		}
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct zebu_highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(value->literal), value->literal = inc_zebu_token(token);
		free_zebu_token(token);
		}
		d = value, g = 2;
		break;
	}
	case 6:
	{
		struct zebu_highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		{
		struct zebu_root* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_root(value->subexpression), value->subexpression = inc_zebu_root(subgrammar);
		free_zebu_root(subgrammar);
		}
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		d = value, g = 2;
		break;
	}
	case 3:
	{
		struct zebu_multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_highest* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_highest(value->left), value->left = inc_zebu_highest(subgrammar);
		free_zebu_highest(subgrammar);
		}
		d = value, g = 3;
		break;
	}
	case 7:
	{
		struct zebu_multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct zebu_multiply* trie = data.data[--yacc.n, --data.n];
			if (trie->left) { free_zebu_highest(value->left); value->left = inc_zebu_highest(trie->left); }
			if (trie->times) { free_zebu_multiply(value->times); value->times = inc_zebu_multiply(trie->times); }
			free_zebu_multiply(trie);
		}
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		{
		struct zebu_highest* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_highest(value->left), value->left = inc_zebu_highest(subgrammar);
		free_zebu_highest(subgrammar);
		}
		d = value, g = 3;
		break;
	}
	case 9:
	{
		struct zebu_multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct zebu_multiply* trie = data.data[--yacc.n, --data.n];
			if (trie->left) { free_zebu_highest(value->left); value->left = inc_zebu_highest(trie->left); }
			if (trie->times) { free_zebu_multiply(value->times); value->times = inc_zebu_multiply(trie->times); }
			free_zebu_multiply(trie);
		}
		{
		struct zebu_token* token = data.data[--yacc.n, --data.n];
		free_zebu_token(token);
		}
		{
		struct zebu_highest* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_highest(value->left), value->left = inc_zebu_highest(subgrammar);
		free_zebu_highest(subgrammar);
		}
		d = value, g = 3;
		break;
	}
	case 2:
	{
		struct zebu_root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
		struct zebu_addition* subgrammar = data.data[--yacc.n, --data.n];
		free_zebu_addition(value->root), value->root = inc_zebu_addition(subgrammar);
		free_zebu_addition(subgrammar);
		}
		d = value, g = 4;
		break;
	}
}
				
				if (g == 7)
				{
					free_zebu_token(td);
					yacc.n = 0, root = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					#ifdef ZEBU_DEBUG
					ddprintf("y = %u\n", y);
					#endif
					
					assert(y < N(zebu_gotos) && g < N(*zebu_gotos));
					
					s = zebu_gotos[y][g];
					
					#ifdef ZEBU_DEBUG
					ddprintf("s = %u\n", s);
					#endif
					
					y = s, push_state(y), push_data(d);
				}
			}
			else
			{
				assert(!"190");
			}
		}
		
		assert(!data.n);
		
		print_zebu_$start(NULL, p_root, "start", root);
		
		free_zebu_$start(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










