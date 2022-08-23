
#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add.h"

void tokenset_add(struct tokenset* this, unsigned token)
{
	ENTER;
	
	dpv(token);
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = arena_realloc(this->arena, this->data, sizeof(*this->data) * this->cap);
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; i < n; i++)
	{
		if (token < this->data[i])
		{
			unsigned temp = this->data[i];
			this->data[i] = token;
			token = temp;
		}
		else if (token > this->data[i])
		{
			;
		}
		else
		{
			EXIT;
			return;
		}
	}
	
	this->data[this->n++] = token;
	EXIT;
}


















