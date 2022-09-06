
#include "kind.h"

struct reductioninfo
{
	struct structinfo* structinfo; // could be NULL
	
	enum reductioninfo_kind kind;
	
	struct string* grammar;
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

