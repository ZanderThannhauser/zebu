
#include <debug.h>

#include "struct.h"
#include "free.h"

static void free_link(struct regex_link* link)
{
	if (link)
	{
		free_link(link->next);
		free(link);
	}
}

void free_regex_ll(struct regex_ll* this)
{
	ENTER;
	
	free_link(this->head);
	free(this);
	
	EXIT;
}

