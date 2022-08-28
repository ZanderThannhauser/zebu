
#ifndef STRUCT_PAIR_H
#define STRUCT_PAIR_H

struct lex_pair
{
	struct lex_state *a, *b;
	
	struct memory_arena* arena;
};

#endif
