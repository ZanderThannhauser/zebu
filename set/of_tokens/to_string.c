
#include <stdio.h>
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "to_string.h"

char* tokenset_to_string(
	const struct tokenset* this)
{
	char* buffer = smalloc(this->n * 30 + 1);
	
	char* moving = buffer;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		moving += sprintf(moving, "%i", this->data[i]);
		
		if (i + 1 < n)
		{
			*moving++ = ',';
			*moving++ = ' ';
		}
	}
	
	*moving = '\0';
	
	return buffer;
}

