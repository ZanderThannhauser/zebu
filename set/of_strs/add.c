
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add.h"

void strset_add(struct strset* this, const char* str)
{
	ENTER;
	
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
		dpvs(str);
		dpvs(this->data[i]);
		
		int cmp = strcmp(str, this->data[i]);
		
		if (cmp < 0)
		{
			const char* temp = this->data[i];
			this->data[i] = str;
			str = temp;
		}
		else if (cmp > 0)
		{
			;
		}
		else
		{
			EXIT;
			return;
		}
	}
	
	dpvs(str);
	
	this->data[this->n++] = str;
	
	EXIT;
}

