
struct iterator;

struct heap
{
	void** data;
	
	unsigned n, cap;
	
	int (*cmp)(const void*, const void*);
};

