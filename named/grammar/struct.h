
#ifndef STRUCT_NAMED_GRAMMAR_H
#define STRUCT_NAMED_GRAMMAR_H

struct named_grammar
{
	char* name;
	struct gegex* grammar;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

#endif
