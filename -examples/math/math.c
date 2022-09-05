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


const unsigned zebu_lexer_starts[33] = {
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
	[26] = 3,
	[27] = 3,
	[28] = 5,
	[29] = 7,
	[30] = 7,
	[31] = 6,
	[32] = 6,
};


const unsigned zebu_lexer_defaults[1] = {
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
	[18][9] = 28,
	[19][2] = 8,
	[19][3] = 9,
	[20][2] = 8,
	[20][3] = 9,
	[21][2] = 8,
	[21][3] = 9,
	[22][2] = 8,
	[22][3] = 9,
};


const unsigned zebu_reduces[33][10] = {
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
	[26][8] = 9,
	[27][8] = 10,
	[28][4] = 6,
	[28][5] = 6,
	[28][6] = 6,
	[28][7] = 6,
	[28][9] = 6,
	[29][6] = 7,
	[29][7] = 7,
	[29][9] = 7,
	[30][6] = 8,
	[30][7] = 8,
	[30][9] = 8,
	[31][9] = 9,
	[32][9] = 10,
};


const unsigned zebu_gotos[23][5] = {
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
	[14][3] = 24,
	[15][2] = 5,
	[15][3] = 25,
	[16][1] = 26,
	[16][2] = 5,
	[16][3] = 6,
	[17][1] = 27,
	[17][2] = 5,
	[17][3] = 6,
	[19][2] = 11,
	[19][3] = 29,
	[20][2] = 11,
	[20][3] = 30,
	[21][1] = 31,
	[21][2] = 11,
	[21][3] = 12,
	[22][1] = 32,
	[22][2] = 11,
	[22][3] = 12,
};


struct token
{
unsigned char* data;
unsigned len;
};
struct __start__
{
	struct root* root;
};

struct addition
{
	struct addition* add;
	struct multiply* left;
	struct addition* minus;
};

struct highest
{
	struct token* literal;
	struct root* subexpression;
};

struct multiply
{
	struct multiply* divide;
	struct highest* left;
	struct multiply* times;
};

struct root
{
	struct addition* root;
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

void print_addition_tree(struct link* links, enum prefix p, const char* name, struct addition* ptree);

void print_highest_tree(struct link* links, enum prefix p, const char* name, struct highest* ptree);

void print_multiply_tree(struct link* links, enum prefix p, const char* name, struct multiply* ptree);

void print_root_tree(struct link* links, enum prefix p, const char* name, struct root* ptree);

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
	printf("\e[34m%s\e[m (\e[36m__start__\e[m): \n", name);
	if (ptree->root)
		print_root_tree(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "root");
	free(new);
}
void print_addition_tree(struct link* links, enum prefix p, const char* name, struct addition* ptree)
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
	printf("\e[34m%s\e[m (\e[36maddition\e[m): \n", name);
	if (ptree->add)
		print_addition_tree(new ?: links, p_not_last_child, "add", ptree->add);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "addition", "add");
	if (ptree->left)
		print_multiply_tree(new ?: links, p_not_last_child, "left", ptree->left);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "multiply", "left");
	if (ptree->minus)
		print_addition_tree(new ?: links, p_last_child, "minus", ptree->minus);
	else
		print_empty_leaf(new ?: links, p_last_child, "addition", "minus");
	free(new);
}
void print_highest_tree(struct link* links, enum prefix p, const char* name, struct highest* ptree)
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
	printf("\e[34m%s\e[m (\e[36mhighest\e[m): \n", name);
	if (ptree->literal)
		print_token_leaf(new ?: links, p_not_last_child, "literal", ptree->literal);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "literal");
	if (ptree->subexpression)
		print_root_tree(new ?: links, p_last_child, "subexpression", ptree->subexpression);
	else
		print_empty_leaf(new ?: links, p_last_child, "root", "subexpression");
	free(new);
}
void print_multiply_tree(struct link* links, enum prefix p, const char* name, struct multiply* ptree)
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
	printf("\e[34m%s\e[m (\e[36mmultiply\e[m): \n", name);
	if (ptree->divide)
		print_multiply_tree(new ?: links, p_not_last_child, "divide", ptree->divide);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "multiply", "divide");
	if (ptree->left)
		print_highest_tree(new ?: links, p_not_last_child, "left", ptree->left);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "highest", "left");
	if (ptree->times)
		print_multiply_tree(new ?: links, p_last_child, "times", ptree->times);
	else
		print_empty_leaf(new ?: links, p_last_child, "multiply", "times");
	free(new);
}
void print_root_tree(struct link* links, enum prefix p, const char* name, struct root* ptree)
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
	printf("\e[34m%s\e[m (\e[36mroot\e[m): \n", name);
	if (ptree->root)
		print_addition_tree(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "addition", "root");
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

void free_addition_tree(struct addition* ptree);

void free_highest_tree(struct highest* ptree);

void free_multiply_tree(struct multiply* ptree);

void free_root_tree(struct root* ptree);

void free___start___tree(struct __start__* ptree)
{
	if (ptree)
	{
		free_root_tree(ptree->root);
		free(ptree);
	}
}

void free_addition_tree(struct addition* ptree)
{
	if (ptree)
	{
		free_addition_tree(ptree->add);
		free_multiply_tree(ptree->left);
		free_addition_tree(ptree->minus);
		free(ptree);
	}
}

void free_highest_tree(struct highest* ptree)
{
	if (ptree)
	{
		free_token(ptree->literal);
		free_root_tree(ptree->subexpression);
		free(ptree);
	}
}

void free_multiply_tree(struct multiply* ptree)
{
	if (ptree)
	{
		free_multiply_tree(ptree->divide);
		free_highest_tree(ptree->left);
		free_multiply_tree(ptree->times);
		free(ptree);
	}
}

void free_root_tree(struct root* ptree)
{
	if (ptree)
	{
		free_addition_tree(ptree->root);
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
			
			char* begin = lexer;
			
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
						assert(!"144");
						#if 0
						l = a, t = b, f = i++;
						ddprintf("l = %u, t == %u, f = %u (saved)\n", l, t, f);
						#endif
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
	case 5:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->root = data.data[--yacc.n, --data.n];
		d = value, g = 5;
		break;
	}
	case 4:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 10:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->minus = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 9:
	{
		struct addition* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->add = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->literal = data.data[--yacc.n, --data.n];
		d = value, g = 2;
		break;
	}
	case 6:
	{
		struct highest* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		free_token(data.data[--yacc.n, --data.n]);
		value->subexpression = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 7:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->times = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 8:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->divide = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 3:
	{
		struct multiply* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->left = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 2:
	{
		struct root* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->root = data.data[--yacc.n, --data.n];
		d = value, g = 4;
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










