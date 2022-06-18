
#include <debug.h>

#include "smalloc.h"
#include "smemdup.h"

void* smemdup(const void* in, size_t size)
{
	void* new = smalloc(size);
	
	memcpy(new, in, size);
	
	return new;
}
