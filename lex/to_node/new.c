
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct dfa_to_id_node* new_dfa_to_id_node(
	unsigned id, struct regex* token)
{
	ENTER;
	
	struct dfa_to_id_node* this = malloc(sizeof(*this));
	
	this->id = id;
	this->token = token;
	
	EXIT;
	return this;
}
