
#ifndef STRUCT_RBUNDLE_H
#define STRUCT_RBUNDLE_H

#include <stdbool.h>

struct regex;

struct rbundle
{
	bool is_nfa;
	
	union
	{
		struct
		{
			struct regex* start;
			struct regex* end;
		} nfa;
		
		struct
		{
			struct regex* dfa;
		};
	};
};

#endif
