
#include <assert.h>

#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add.h"

bool regexset_add(struct regexset* this, struct regex* ptr)
{
	ENTER;
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = arena_realloc(this->arena, this->data, sizeof(*this->data) * this->cap);
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; i < n; )
	{
		struct regex* ele = this->data[i];
		
		if (ptr < ele)
		{
			this->data[i] = ptr;
			ptr = ele;
		}
		else if (ptr > ele)
		{
			i++;
		}
		else
		{
			EXIT;
			return false;
		}
	}
	
	this->data[this->n++] = ptr;
	
	EXIT;
	return true;
}










