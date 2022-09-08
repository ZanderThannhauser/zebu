#include "lisp.h"

#define _GNU_SOURCE

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

const unsigned zebu_shifts[21][8] = {
	[1][2] = 2,
	[1][3] = 3,
	[1][4] = 4,
	[1][5] = 5,
	[4][2] = 2,
	[4][3] = 3,
	[4][4] = 4,
	[4][5] = 5,
	[5][2] = 8,
	[5][3] = 9,
	[5][4] = 10,
	[5][5] = 11,
	[10][2] = 8,
	[10][3] = 9,
	[10][4] = 10,
	[10][5] = 11,
	[11][2] = 8,
	[11][3] = 9,
	[11][4] = 10,
	[11][5] = 11,
	[12][2] = 8,
	[12][3] = 9,
	[12][4] = 10,
	[12][5] = 11,
	[12][7] = 15,
	[14][2] = 8,
	[14][3] = 9,
	[14][4] = 10,
	[14][5] = 11,
	[14][7] = 18,
	[17][2] = 8,
	[17][3] = 9,
	[17][4] = 10,
	[17][5] = 11,
	[17][7] = 15,
	[20][2] = 8,
	[20][3] = 9,
	[20][4] = 10,
	[20][5] = 11,
	[20][7] = 18,
};


const unsigned zebu_reduces[23][8] = {
	[2][6] = 1,
	[3][6] = 2,
	[6][6] = 3,
	[7][6] = 4,
	[8][2] = 1,
	[8][3] = 1,
	[8][4] = 1,
	[8][5] = 1,
	[8][7] = 1,
	[9][2] = 2,
	[9][3] = 2,
	[9][4] = 2,
	[9][5] = 2,
	[9][7] = 2,
	[13][2] = 4,
	[13][3] = 4,
	[13][4] = 4,
	[13][5] = 4,
	[13][7] = 4,
	[15][6] = 5,
	[16][6] = 6,
	[18][2] = 5,
	[18][3] = 5,
	[18][4] = 5,
	[18][5] = 5,
	[18][7] = 5,
	[19][2] = 6,
	[19][3] = 6,
	[19][4] = 6,
	[19][5] = 6,
	[19][7] = 6,
	[21][6] = 7,
	[22][2] = 7,
	[22][3] = 7,
	[22][4] = 7,
	[22][5] = 7,
	[22][7] = 7,
};
<<<<<<< HEAD
const unsigned zebu_lexer[9][123] = {
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
	[8][40] = 2,
	[8][41] = 9,
	[8][48] = 3,
	[8][49] = 3,
	[8][50] = 3,
	[8][51] = 3,
	[8][52] = 3,
	[8][53] = 3,
	[8][54] = 3,
	[8][55] = 3,
	[8][56] = 3,
	[8][57] = 3,
	[8][65] = 4,
	[8][66] = 4,
	[8][67] = 4,
	[8][68] = 4,
	[8][69] = 4,
	[8][70] = 4,
	[8][71] = 4,
	[8][72] = 4,
	[8][73] = 4,
	[8][74] = 4,
	[8][75] = 4,
	[8][76] = 4,
	[8][77] = 4,
	[8][78] = 4,
	[8][79] = 4,
	[8][80] = 4,
	[8][81] = 4,
	[8][82] = 4,
	[8][83] = 4,
	[8][84] = 4,
	[8][85] = 4,
	[8][86] = 4,
	[8][87] = 4,
	[8][88] = 4,
	[8][89] = 4,
	[8][90] = 4,
	[8][96] = 5,
	[8][97] = 4,
	[8][98] = 4,
	[8][99] = 4,
	[8][100] = 4,
	[8][101] = 4,
	[8][102] = 4,
	[8][103] = 4,
	[8][104] = 4,
	[8][105] = 4,
	[8][106] = 4,
	[8][107] = 4,
	[8][108] = 4,
	[8][109] = 4,
	[8][110] = 4,
	[8][111] = 4,
	[8][112] = 4,
	[8][113] = 4,
	[8][114] = 4,
	[8][115] = 4,
	[8][116] = 4,
	[8][117] = 4,
	[8][118] = 4,
	[8][119] = 4,
	[8][120] = 4,
	[8][121] = 4,
	[8][122] = 4,
=======


const unsigned zebu_gotos[21][3] = {
	[1][1] = 6,
	[4][1] = 7,
	[5][1] = 12,
	[10][1] = 13,
	[11][1] = 14,
	[12][1] = 17,
	[12][2] = 16,
	[14][1] = 20,
	[14][2] = 19,
	[17][1] = 17,
	[17][2] = 21,
	[20][1] = 20,
	[20][2] = 22,
};


const unsigned zebu_lexer[7][123] = {
	[1][9] = 1,
	[1][10] = 1,
	[1][32] = 1,
	[1][40] = 4,
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
	[1][65] = 6,
	[1][66] = 6,
	[1][67] = 6,
	[1][68] = 6,
	[1][69] = 6,
	[1][70] = 6,
	[1][71] = 6,
	[1][72] = 6,
	[1][73] = 6,
	[1][74] = 6,
	[1][75] = 6,
	[1][76] = 6,
	[1][77] = 6,
	[1][78] = 6,
	[1][79] = 6,
	[1][80] = 6,
	[1][81] = 6,
	[1][82] = 6,
	[1][83] = 6,
	[1][84] = 6,
	[1][85] = 6,
	[1][86] = 6,
	[1][87] = 6,
	[1][88] = 6,
	[1][89] = 6,
	[1][90] = 6,
	[1][96] = 7,
	[1][97] = 6,
	[1][98] = 6,
	[1][99] = 6,
	[1][100] = 6,
	[1][101] = 6,
	[1][102] = 6,
	[1][103] = 6,
	[1][104] = 6,
	[1][105] = 6,
	[1][106] = 6,
	[1][107] = 6,
	[1][108] = 6,
	[1][109] = 6,
	[1][110] = 6,
	[1][111] = 6,
	[1][112] = 6,
	[1][113] = 6,
	[1][114] = 6,
	[1][115] = 6,
	[1][116] = 6,
	[1][117] = 6,
	[1][118] = 6,
	[1][119] = 6,
	[1][120] = 6,
	[1][121] = 6,
	[1][122] = 6,
	[2][9] = 2,
	[2][10] = 2,
	[2][32] = 2,
	[3][9] = 3,
	[3][10] = 3,
	[3][32] = 3,
	[3][40] = 4,
	[3][41] = 9,
	[3][48] = 5,
	[3][49] = 5,
	[3][50] = 5,
	[3][51] = 5,
	[3][52] = 5,
	[3][53] = 5,
	[3][54] = 5,
	[3][55] = 5,
	[3][56] = 5,
	[3][57] = 5,
	[3][65] = 6,
	[3][66] = 6,
	[3][67] = 6,
	[3][68] = 6,
	[3][69] = 6,
	[3][70] = 6,
	[3][71] = 6,
	[3][72] = 6,
	[3][73] = 6,
	[3][74] = 6,
	[3][75] = 6,
	[3][76] = 6,
	[3][77] = 6,
	[3][78] = 6,
	[3][79] = 6,
	[3][80] = 6,
	[3][81] = 6,
	[3][82] = 6,
	[3][83] = 6,
	[3][84] = 6,
	[3][85] = 6,
	[3][86] = 6,
	[3][87] = 6,
	[3][88] = 6,
	[3][89] = 6,
	[3][90] = 6,
	[3][96] = 7,
	[3][97] = 6,
	[3][98] = 6,
	[3][99] = 6,
	[3][100] = 6,
	[3][101] = 6,
	[3][102] = 6,
	[3][103] = 6,
	[3][104] = 6,
	[3][105] = 6,
	[3][106] = 6,
	[3][107] = 6,
	[3][108] = 6,
	[3][109] = 6,
	[3][110] = 6,
	[3][111] = 6,
	[3][112] = 6,
	[3][113] = 6,
	[3][114] = 6,
	[3][115] = 6,
	[3][116] = 6,
	[3][117] = 6,
	[3][118] = 6,
	[3][119] = 6,
	[3][120] = 6,
	[3][121] = 6,
	[3][122] = 6,
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
	[6][65] = 6,
	[6][66] = 6,
	[6][67] = 6,
	[6][68] = 6,
	[6][69] = 6,
	[6][70] = 6,
	[6][71] = 6,
	[6][72] = 6,
	[6][73] = 6,
	[6][74] = 6,
	[6][75] = 6,
	[6][76] = 6,
	[6][77] = 6,
	[6][78] = 6,
	[6][79] = 6,
	[6][80] = 6,
	[6][81] = 6,
	[6][82] = 6,
	[6][83] = 6,
	[6][84] = 6,
	[6][85] = 6,
	[6][86] = 6,
	[6][87] = 6,
	[6][88] = 6,
	[6][89] = 6,
	[6][90] = 6,
	[6][97] = 6,
	[6][98] = 6,
	[6][99] = 6,
	[6][100] = 6,
	[6][101] = 6,
	[6][102] = 6,
	[6][103] = 6,
	[6][104] = 6,
	[6][105] = 6,
	[6][106] = 6,
	[6][107] = 6,
	[6][108] = 6,
	[6][109] = 6,
	[6][110] = 6,
	[6][111] = 6,
	[6][112] = 6,
	[6][113] = 6,
	[6][114] = 6,
	[6][115] = 6,
	[6][116] = 6,
	[6][117] = 6,
	[6][118] = 6,
	[6][119] = 6,
	[6][120] = 6,
	[6][121] = 6,
	[6][122] = 6,
>>>>>>> dev
};


const unsigned zebu_lexer_starts[23] = {
	[1] = 1,
	[2] = 2,
	[3] = 2,
	[4] = 1,
	[5] = 1,
	[6] = 2,
	[7] = 2,
	[8] = 3,
	[9] = 3,
	[10] = 1,
	[11] = 1,
	[12] = 3,
	[13] = 3,
	[14] = 3,
	[15] = 2,
	[16] = 2,
	[17] = 3,
	[18] = 3,
	[19] = 3,
	[20] = 3,
	[21] = 2,
	[22] = 3,
};


const unsigned zebu_lexer_accepts[10] = {
	[4] = 5,
	[5] = 2,
	[6] = 3,
	[7] = 4,
	[8] = 6,
	[9] = 7,
};


const unsigned zebu_lexer_EOFs[3] = {
	[2] = 8,
};
<<<<<<< HEAD
const unsigned zebu_accepts[10] = {
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 5,
	[7] = 6,
	[9] = 8,
=======


struct token
{
unsigned char* data;
unsigned len, refcount;
>>>>>>> dev
};
struct __start__
{
	struct value* root;
	unsigned refcount;
};
<<<<<<< HEAD
=======

struct value
{
	struct value* backtack;
	struct token* identifier;
	struct {
		struct value** data;
		unsigned n, cap;
	} list;
	struct token* number;
	unsigned refcount;
};
>>>>>>> dev



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
void print___start___ptree(struct link* links, enum prefix p, const char* name, struct __start__* ptree);

void print_value_ptree(struct link* links, enum prefix p, const char* name, struct value* ptree);

void print___start___ptree(struct link* links, enum prefix p, const char* name, struct __start__* ptree)
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
		print_value_ptree(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "root");
	free(new);
}
void print_value_ptree(struct link* links, enum prefix p, const char* name, struct value* ptree)
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
	if (ptree->backtack)
		print_value_ptree(new ?: links, p_not_last_child, "backtack", ptree->backtack);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "value", "backtack");
	if (ptree->identifier)
		print_token_leaf(new ?: links, p_not_last_child, "identifier", ptree->identifier);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "identifier");
	if (ptree->list.n)
	{
		for (unsigned i = 0, n = ptree->list.n; i < n; i++)
		{
			char label[4 + 30];
			snprintf(label, sizeof(label), "list[%u]", i);
			print_value_ptree(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->list.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "value[]", "list");
	}
	if (ptree->number)
		print_token_leaf(new ?: links, p_last_child, "number", ptree->number);
	else
		print_empty_leaf(new ?: links, p_last_child, "token", "number");
	free(new);
}


struct token* inc_token(struct token* this)
{
	if (this) this->refcount++;
	return this;
}
struct __start__* inc___start___ptree(struct __start__* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct value* inc_value_ptree(struct value* ptree)
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
void free___start___ptree(struct __start__* ptree);

void free_value_ptree(struct value* ptree);

void free___start___ptree(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_value_ptree(ptree->root);
		free(ptree);
	}
}

void free_value_ptree(struct value* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_value_ptree(ptree->backtack);
		free_token(ptree->identifier);
		for (unsigned i = 0, n = ptree->list.n; i < n; i++)
			free_value_ptree(ptree->list.data[i]);
		free(ptree->list.data);
		free_token(ptree->number);
		free(ptree);
	}
}



#define argv0 (program_invocation_name)

#define N(array) (sizeof(array) / sizeof(*array))

struct cmdln
{
	const char* input;
};

void usage(int code)
{
	fprintf(stderr, "usage: %s <path/to/input/file>\n", argv0);
	exit(code);
}

struct cmdln* process_cmdln(int argc, char* const* argv)
{
	int opt;
	
	const char* input = NULL;
	
	while ((opt = getopt(argc, argv, "h")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			default:
				usage(1);
		}
	}
	
	input = argv[optind++];
	
	if (!input)
		usage(1);
	
	struct cmdln* retval = malloc(sizeof(*retval));
	assert(retval);
	retval->input = input;
	return retval;
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

void* parse(FILE* stream)
{
	void* root;
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data; unsigned n, cap; } data = {};
	struct { unsigned char* data; unsigned n, cap; } lexer = {};
	
	void push_state(unsigned y)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		yacc.data[yacc.n++] = y;
	}
	
	void push_data(void* d)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		data.data[data.n++] = d;
	}
	
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
	
	unsigned y, t, s, r;
	void* td;
	
	void read_token(unsigned l)
	{
		void append(unsigned char c)
		{
			while (lexer.n + 1 >= lexer.cap)
			{
				lexer.cap = lexer.cap << 1 ?: 1;
				ddprintf("lexer.cap == %u\n", lexer.cap);
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		unsigned i = 0, f, a, b, c;
		
		t = 0;
		
		ddprintf("l = %u\n", l);
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				char escaped[10];
				
				escape(escaped, c);
				
				printf("c = '%s' (0x%X) (from cache)\n", escaped, c);
				
				assert(!"163");
				#if 0
				next = 0
					?: (state < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[state][c] : 0)
					?: (state < N(zebu_defaults) ? zebu_defaults[state] : 0);
				#endif
			}
			else if ((c = getc(stream)) != EOF)
			{
				append(c);
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X)\n", escaped, c);
				
				a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				ddprintf("c = <EOF>\n");
				
				a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
			}
			
			b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
			
			ddprintf("a = %u, b = %u\n", a, b);
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = i++;
					ddprintf("l = %u\n", l);
				}
				else
				{
					l = a, i++;
					ddprintf("l = %u\n", l);
				}
			}
			else if (b)
			{
				if (c != EOF)
				{
					lexer.n--, ungetc(c, stream);
				}
				
				ddprintf("lexer.n == %u\n", lexer.n);
				ddprintf("lexer: \"%.*s\"\n", lexer.n, lexer.data);
				
				append('\0');
				
				struct token* token = malloc(sizeof(*token));
				token->refcount = 1;
				token->data = memcpy(malloc(lexer.n), lexer.data, lexer.n);
				t = b, td = token, lexer.n = 0;
				break;
			}
			else if (t)
			{
				assert(!"235");
				#if 0
				memmove(lexer.data, lexer.data + fallback, lexer.n - fallback);
				lexer.n -= fallback;
				return token;
				#endif
			}
			else
			{
				assert(!"168");
			}
		}
	}
	
	push_state(1), y = 1, read_token(1);
	
	ddprintf("y = %u, t = %u\n", y, t);
	
	while (yacc.n)
	{
		if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
		{
			ddprintf("s == %u\n", s);
			
			y = s, push_state(y), push_data(td);
			
			read_token(zebu_lexer_starts[y]);
			
			ddprintf("t = %u\n", t);
		}
		else if (y < N( zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
		{
			ddprintf("r == %u\n", r);
			
			unsigned g;
			void* d;
			
			switch (r)
{
	case 5:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 7:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->backtack) { free_value_ptree(value->backtack); value->backtack = inc_value_ptree(trie->backtack); }
			if (trie->identifier) { free_token(value->identifier); value->identifier = inc_token(trie->identifier); }
			if (trie->list.n)
			{
				while (value->list.n + trie->list.n > value->list.cap)
				{
					value->list.cap = value->list.cap << 1 ?: 1;
					value->list.data = realloc(value->list.data, sizeof(*value->list.data) * value->list.cap);
				}
				memmove(value->list.data + trie->list.n, value->list.data, sizeof(*value->list.data) * value->list.n);
				for (unsigned i = 0, n = trie->list.n; i < n; i++)
					value->list.data[i] = inc_value_ptree(trie->list.data[i]);
				value->list.n += trie->list.n;
			}
			if (trie->number) { free_token(value->number); value->number = inc_token(trie->number); }
			free_value_ptree(trie);
		}
		if (value->list.n == value->list.cap)
		{
			value->list.cap = value->list.cap << 1 ?: 1;
			value->list.data = realloc(value->list.data, sizeof(*value->list.data) * value->list.cap);
		}
		memmove(value->list.data + 1, value->list.data, sizeof(*value->list.data) * value->list.n);
		value->list.data[0] = data.data[--yacc.n, --data.n], value->list.n++;
		d = value, g = 2;
		break;
	}
	case 3:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_value_ptree(value->root), value->root = data.data[--yacc.n, --data.n];
		d = value, g = 3;
		break;
	}
	case 4:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_value_ptree(value->backtack), value->backtack = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 6:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->backtack) { free_value_ptree(value->backtack); value->backtack = inc_value_ptree(trie->backtack); }
			if (trie->identifier) { free_token(value->identifier); value->identifier = inc_token(trie->identifier); }
			if (trie->list.n)
			{
				while (value->list.n + trie->list.n > value->list.cap)
				{
					value->list.cap = value->list.cap << 1 ?: 1;
					value->list.data = realloc(value->list.data, sizeof(*value->list.data) * value->list.cap);
				}
				memmove(value->list.data + trie->list.n, value->list.data, sizeof(*value->list.data) * value->list.n);
				for (unsigned i = 0, n = trie->list.n; i < n; i++)
					value->list.data[i] = inc_value_ptree(trie->list.data[i]);
				value->list.n += trie->list.n;
			}
			if (trie->number) { free_token(value->number); value->number = inc_token(trie->number); }
			free_value_ptree(trie);
		}
		if (value->list.n == value->list.cap)
		{
			value->list.cap = value->list.cap << 1 ?: 1;
			value->list.data = realloc(value->list.data, sizeof(*value->list.data) * value->list.cap);
		}
		memmove(value->list.data + 1, value->list.data, sizeof(*value->list.data) * value->list.n);
		value->list.data[0] = data.data[--yacc.n, --data.n], value->list.n++;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 2:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->identifier), value->identifier = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->number), value->number = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
}
			
			if (g == 3)
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
			assert(!"266");
		}
	}
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return root;
}

int main(int argc, char* const* argv)
{
	struct cmdln* cmdln = process_cmdln(argc, argv);
	
	FILE* input = fopen(cmdln->input, "r");
	
	if (!input)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, cmdln->input),
		exit(1);
	}
	
	void* root = parse(input);
	
	print___start___ptree(NULL, p_root, "start", root);
	
	free___start___ptree(root);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















