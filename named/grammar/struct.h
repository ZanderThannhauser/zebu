
#ifndef STRUCT_NAMED_GRAMMAR_H
#define STRUCT_NAMED_GRAMMAR_H

struct named_grammar
{
	char* name;
	struct gegex* start;
	struct gegex* end;
};

#endif
