
#ifndef STRUCT_PAIR_H
#define STRUCT_PAIR_H

struct pair
{
	struct regex *a, *b;
	
	struct memory_arena* arena;
};

#endif
