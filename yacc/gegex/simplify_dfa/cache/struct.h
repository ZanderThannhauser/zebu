
#include <stdbool.h>

struct gegex_cache
{
	const struct gegex *a, *b; // must be the firsts
	
	bool are_equal;
};
