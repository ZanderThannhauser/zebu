
#include <stdlib.h>

#include <memory/smalloc.h>

#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "new.h"
#include "difference.h"

struct charset* charset_difference(
	const struct charset* a,
	const struct charset* b,
	bool is_complement)
{
	ENTER;
	
	size_t n = 0;
	
	char* chars = smalloc(sizeof(*chars) * a->len);
	
	size_t a_i = 0, a_n = a->len;
	size_t b_i = 0, b_n = b->len;
	
	while (a_i < a_n && b_i < b_n)
	{
		char a_ele = a->chars[a_i], b_ele = b->chars[b_i];
		
		if (a_ele < b_ele)
			chars[n++] = a_ele, a_i++;
		else if (a_ele > b_ele)
			b_i++;
		else
			a_i++, b_i++;
	}
	
	while (a_i < a_n)
		chars[n++] = a->chars[a_i++];
	
	struct charset* new = new_charset(chars, n, is_complement);
	
	free(chars);
	
	EXIT;
	return new;
}




















