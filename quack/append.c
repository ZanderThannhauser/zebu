
#include <string.h>

#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "append.h"

void quack_append(
	struct quack* this,
	void* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		unsigned old_cap = this->cap, new_cap = old_cap << 1 ?: 1;
		
		this->data = srealloc(this->data, sizeof(*this->data) * new_cap);
		
		if (this->i)
		{
			unsigned new_i = new_cap - old_cap + this->i;
			
			memmove(
				/* dst: */ &this->data[new_i],
				/* src: */ &this->data[this->i],
				/* len: */ sizeof(*this->data) * (old_cap - this->i));
			
			this->i = new_i;
			dpv(this->i);
		}
		
		this->cap = new_cap;
		dpv(this->cap);
	}
	
	this->data[(this->i + this->n++) % this->cap] = element;
	
	dpv(this->n);
	
	EXIT;
}

