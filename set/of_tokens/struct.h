
struct tokenset
{
	unsigned *data, n, cap;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

