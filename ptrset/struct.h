
struct ptrset
{
	int (*cmp)(const void*, const void*);
	
	union
	{
		const void** data;
		const char** datac;
	};
	
	unsigned cap, n;
};

