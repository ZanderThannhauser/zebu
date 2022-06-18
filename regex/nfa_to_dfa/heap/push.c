
#include <debug.h>

#include <memory/srealloc.h>

#include "../iterator/compare.h"

#include "struct.h"
#include "push.h"

void heap_push(struct heap* this, struct iterator* new)
{
	ENTER;
	
	if (this->n + 1 >= this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	size_t i;
	struct iterator** const data = this->data, *swap;
	
	data[this->n] = new;
	
	for (i = this->n; i > 0 && compare_iterators(data[i / 2], data[i]) > 0; i >>= 1)
	{
		swap = data[i];
		data[i] = data[i / 2];
		data[i / 2] = swap;
	}
	
	this->n++;
	
	EXIT;
}
















