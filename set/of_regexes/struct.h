
struct regexset
{
	struct regex** data;
	
	unsigned cap, n;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

