
#ifndef STRUCT_STRSET
#define STRUCT_STRSET

struct strset
{
	const char** data;
	unsigned cap, n;
	
	struct memory_arena* arena;
};

#endif
