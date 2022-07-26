
#include <debug.h>

#ifdef DEBUGGING
#include <set/of_tokens/to_string.h>
#endif

#include <set/of_tokens/compare.h>

#include "struct.h"
#include "add.h"

struct tokenset* tokensetset_add(struct tokensetset* this, struct tokenset* ts)
{
	struct tokenset* found = NULL;
	ENTER;
	
	dpv(ts);
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; !found && i < n; i++)
	{
		struct tokenset* ele = this->data[i];
		
		int cmp = compare_tokensets(ts, ele);
		
		if (cmp < 0)
		{
			this->data[i] = ts;
			ts = ele;
		}
		else if (cmp > 0)
		{
			;
		}
		else
		{
			found = ele;
		}
	}
	
	if (!found)
	{
		this->data[this->n++] = ts;
	}
	
	#if 0
	#ifdef DEBUGGING
	{
		unsigned n;
		for (i = 0, n = this->n; i < n; i++)
		{
			char* label = tokenset_to_string(this->data[i]);
			dpvs(label);
			free(label);
		}
		
/*		CHECK_NTH(4);*/
		getchar();
	}
	#endif
	#endif
	
	EXIT;
	return found;
}

















