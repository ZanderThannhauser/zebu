
struct reductioninfo
{
	struct stringset* tags; // could be null
	
	struct string* grammar; // could be null (indicating token)
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

