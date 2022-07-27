
#include <assert.h>

#include <debug.h>

#ifdef DEBUGGING
#include "to_string.h"
#endif

#include "struct.h"
#include "is_disjoint.h"

bool tokenset_is_disjoint(
	const struct tokenset* a,
	const struct tokenset* b)
{
	bool is_disjoint = true;
	ENTER;
	
	#ifdef DEBUGGING
	{
		char* a_label = tokenset_to_string(a);
		char* b_label = tokenset_to_string(b);
		
		dpvs(a_label);
		dpvs(b_label);
		
		free(a_label), free(b_label);
	}
	#endif
	
	unsigned i = 0, n = a->n;
	unsigned j = 0, m = b->n;
	
	while (is_disjoint && i < n && j < m)
	{
		unsigned a_ele = a->data[i];
		unsigned b_ele = b->data[j];
		
		if (a_ele < b_ele)
			i++;
		else if (a_ele > b_ele)
			j++;
		else
			is_disjoint = false;
	}
	
	dpvb(is_disjoint);
	
	EXIT;
	return is_disjoint;
}

