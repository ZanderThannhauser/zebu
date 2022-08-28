
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void quack_foreach(
	struct quack* this,
	void (*runme)(void* ptr))
{
	ENTER;
	
	for (unsigned i = 0; i < this->n; i++)
	{
		runme(this->data[(this->i + i) % this->cap]);
	}
	
	EXIT;
}

