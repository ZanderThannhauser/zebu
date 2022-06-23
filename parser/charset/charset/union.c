
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "new.h"
#include "union.h"

struct charset* charset_union(
	const struct charset* a,
	const struct charset* b,
	bool is_complement)
{
	ENTER;
	
	char* chars = NULL;
	size_t n = 0, cap = 0;
	
	void append(char c)
	{
		if (n + 1 > cap)
			chars = srealloc(chars, (cap = cap << 1 ?: 1));
		chars[n++] = c;
	}
	
	size_t a_i = 0, a_n = a->len;
	size_t b_i = 0, b_n = b->len;
	
	while (a_i < a_n && b_i < b_n)
	{
		char a_ele = a->chars[a_i];
		char b_ele = b->chars[b_i];
		
		if (a_ele < b_ele)
			append(a_ele), a_i++;
		else if (a_ele > b_ele)
			append(b_ele), b_i++;
		else
			append(a_ele), a_i++, b_i++;
	}
	
	while (a_i < a_n)
		append(a->chars[a_i++]);
	
	while (b_i < b_n)
		append(b->chars[b_i++]);
	
	struct charset* new = new_charset(chars, n, is_complement);
	
	EXIT;
	
	return new;
}




















