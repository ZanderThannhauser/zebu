
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
	
	struct memory_arena* arena;
};

