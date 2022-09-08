
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_range.h"

#include "0.highest.h"
#include "1.range.h"

static unsigned char max(charset_t value)
{
	for (unsigned i = 255; 1 <= i + 1; i--)
		if (value[i >> 4] & (1 << (i & 0xF)))
			return i;
	return 0;
}

static unsigned char min(charset_t value)
{
	for (unsigned i = 0, n = 256; i < n; i++)
		if (value[i >> 4] & (1 << (i & 0xF)))
			return i;
	return 255;
}

charset_t read_range_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_highest_charset(tokenizer, scope);
	
	if (tokenizer->token == t_hypen)
	{
		read_token(tokenizer, charset_inside_range_machine);
		
		charset_t right = read_highest_charset(tokenizer, scope);
		
		unsigned char l = min(left), r = max(right);
		
		dpv(l);
		dpv(r);
		
		charset_t range = {};
		
		for (unsigned i = l; i <= r; i++)
			range[i >> 4] |= (1 << (i & 0xF));
		
		EXIT;
		return range;
	}
	else
	{
		EXIT;
		return left;
	}
}








