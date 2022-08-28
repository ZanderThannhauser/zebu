
#include <debug.h>

#include "struct.h"
#include "append.h"

void quack_append(
	struct quack* this,
	void* element)
{
	ENTER;
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[(this->i + this->n++) % this->cap] = element;
	
	dpv(this->n);
	
	EXIT;
}

