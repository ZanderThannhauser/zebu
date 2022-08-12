
#include <stdlib.h>

#include <debug.h>

#include "dlink.h"
#include "struct.h"
#include "free.h"

static void free_dlink(struct dlink* dlink)
{
	ENTER;
	
	if (dlink)
	{
		switch (dlink->left.kind)
		{
			case dk_literal: break;
			case dk_regex: break;
			case dk_string:
				free(dlink->left.s.chars);
				break;
		}
		
		switch (dlink->right.kind)
		{
			case dk_literal: break;
			case dk_regex: break;
			case dk_string:
				free(dlink->right.s.chars);
				break;
		}
		
		free_dlink(dlink->next);
		
		free(dlink);
	}
	
	EXIT;
}

void free_options(struct options* this)
{
	ENTER;
	
	free(this->start);
	
	free_dlink(this->disambiguatations.head);
	
	free(this);
	
	EXIT;
}

