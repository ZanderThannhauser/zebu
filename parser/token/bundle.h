
#ifndef STRUCT_BUNDLE_H
#define STRUCT_BUNDLE_H

#include <stdbool.h>

struct regex;

struct bundle
{
	bool is_nfa;
	struct regex* regex;
};

#endif
