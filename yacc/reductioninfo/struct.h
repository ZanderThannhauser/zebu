
#include "kind.h"

struct reductioninfo
{
	struct stringset* tags; // could be null
	
	enum reductioninfo_kind kind;
	
	struct string* grammar;
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

