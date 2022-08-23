
struct regexset
{
	struct regex** data;
	
	unsigned cap, n;
	
	struct memory_arena* arena;
};

