
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add.h"

void gegexset_add(struct gegexset* this, struct gegex* ptr)
{
	ENTER;
	
	dpv(ptr);
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		#ifdef WITH_ARENAS
		this->data = arena_realloc(this->arena, this->data, sizeof(*this->data) * this->cap);
		#else
		this->data = realloc(this->data, sizeof(*this->data) * this->cap);
		#endif
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; i < n; i++)
	{
		struct gegex* ele = this->data[i];
		
		if (ptr < ele)
		{
			this->data[i] = ptr;
			ptr = ele;
		}
		else if (ptr > ele)
		{
			;
		}
		else
		{
			TODO;
		}
	}
	
	this->data[this->n++] = ptr;
	EXIT;
}

