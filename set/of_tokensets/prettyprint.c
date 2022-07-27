
#include <stdlib.h>

#include <debug.h>

#include <set/of_tokens/to_string.h>

#include "struct.h"
#include "prettyprint.h"

void tokensetset_prettyprint(
	const struct tokensetset* this)
{
	ENTER;
	dpv(this->n);
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		char* value = tokenset_to_string(this->data[i]);
		dpvs(value);
		free(value);
	}
	EXIT;
}

