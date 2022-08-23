
struct tokensetset
{
	struct tokenset** data; // do I own these? tell free()
	
	unsigned cap, n;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

