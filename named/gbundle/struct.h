
#ifndef STRUCT_NAMED_GRAMMAR_H
#define STRUCT_NAMED_GRAMMAR_H

struct named_gbundle
{
	char* name;
	struct gegex* start;
	struct gegex* end;
};

#endif
