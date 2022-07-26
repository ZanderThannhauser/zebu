
#include <debug.h>

#include "struct.h"
#include "contains.h"

static int cmp(const void* a, const void* b)
{
	const void *const *A = a, *const*B = b;
	a = *A, b = *B;
	if (a > b)
		return +1;
	if (a < b)
		return -1;
	return 0;
}

bool tokensetset_contains(
	struct tokensetset* this,
	const void* ptr)
{
	ENTER;
	
	TODO;
	#if 0
	dpv(this->n);
	dpv(ptr);
	
	bool found = !!bsearch(
		/* void* key: */ &ptr,
		/* void* base: */ this->data,
		/* size_t nmemb: */ this->n,
		/* size_t size: */ sizeof(*this->data),
		/* cmp function: */ cmp);
	
	dpvb(found);
	
	EXIT;
	return found;
	#endif
}

