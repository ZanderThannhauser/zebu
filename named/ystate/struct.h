
#ifndef STRUCT_NAMED_GRAMMAR_H
#define STRUCT_NAMED_GRAMMAR_H

struct named_ystate
{
	char* name; // free me
	struct yacc_state* ystate;
};

#endif
