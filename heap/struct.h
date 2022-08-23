
struct iterator;

struct heap
{
	union
	{
		void** data;
		struct iterator** datai;
	};
	
	unsigned n, cap;
	
	int (*cmp)(const void*, const void*);
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

