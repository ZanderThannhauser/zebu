
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <string/struct.h>

#include "struct.h"
#include "build_absolute_name.h"

struct string* scope_build_absolute_name(
	struct scope* this,
	struct string* suffix)
{
	ENTER;
	
	char* full = malloc(this->prefix.n + 1 + suffix->len + 1), *m = full;
	
	if (this->prefix.n)
	{
		memcpy(m, this->prefix.chars, this->prefix.n);
		m += this->prefix.n;
		*m++ = '.';
	}
	
	memcpy(m, suffix->chars, suffix->len);
	m += suffix->len;
	*m = '\0';
	
	dpvs(full);
	
	struct string* retval = new_string_without_copy(full);
	
	EXIT;
	return retval;
}
