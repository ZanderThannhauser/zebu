
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool tokenset_contains(
	struct tokenset* this,
	unsigned token)
{
	ENTER;
	
	dpv(token);
	
	unsigned s = 0, e = this->n - 1;
	
	while (s + 1 <= e + 1)
	{
		dpv(s);
		dpv(e);
		
		unsigned m = s + (e - s) / 2, ele = this->data[m];
		
		dpv(m);
		dpv(ele);
		
		if (ele > token)
			e = m - 1;
		else if (ele < token)
			s = m + 1;
		else
		{
			ddprintf("return true;\n");
			EXIT;
			return true;
		}
	}
	
	ddprintf("return false;\n");
	EXIT;
	return false;
}
