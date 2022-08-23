
#ifndef STRUCT_PAIR_H
#define STRUCT_PAIR_H

struct gegex_pair
{
	struct gegex *a, *b;
	
	struct memory_arena* arena;
};

#endif
