
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct dfa_from_id_node* new_dfa_from_id_node(unsigned id, struct regex* token)
{
	ENTER;
	
	struct dfa_from_id_node* this = smalloc(sizeof(*this));
	
	this->id = id;
	this->token = token;
	
	EXIT;
	return this;
}

