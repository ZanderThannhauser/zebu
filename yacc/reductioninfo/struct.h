
struct reductioninfo
{
	struct string* tag;
	
	unsigned index;
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

