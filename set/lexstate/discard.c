
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void lexstateset_discard(
	struct lexstateset* this,
	struct lex_state* element)
{
	ENTER;
	
	dpv(element);
	
	void* item = avl_delete(this->tree, element);
	
	if (item)
	{
		this->len--;
		
		dpv(this->len);
	}
	
	EXIT;
}

