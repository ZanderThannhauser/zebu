
#ifndef STRUCT_RBUNDLE_H
#define STRUCT_RBUNDLE_H

#include <stdbool.h>

struct regex;

struct rbundle
{
	struct regex* start;
	struct regex* accepts; // if NULL: state machine is a DFA
};

#endif
