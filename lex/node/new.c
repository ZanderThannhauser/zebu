
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct node* new_node(unsigned id, struct regex* token)
{
	ENTER;
	
	struct node* this = smalloc(sizeof(*this));
	
	this->id = id;
	this->token = token;
	
	EXIT;
	return this;
}

