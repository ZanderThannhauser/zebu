
#include <debug.h>

#include <yacc/stateinfo/compare.h>

#include "struct.h"
#include "compare.h"

int compare_stateinfo_to_states(const void* a, const void* b)
{
	const struct stateinfo_to_state* A = a, *B = b;
	return compare_yacc_stateinfos(A->stateinfo, B->stateinfo);
}

