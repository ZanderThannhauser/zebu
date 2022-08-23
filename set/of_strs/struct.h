
#ifndef STRUCT_STRSET
#define STRUCT_STRSET

struct strset
{
	const char** data;
	unsigned cap, n;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

#endif
