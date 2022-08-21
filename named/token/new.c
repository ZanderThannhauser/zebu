
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct named_token* new_named_token(
	char* name,
	struct regex* token)
{
	ENTER;
	
	TODO;
	#if 0
	struct named_token* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->token = token;
	
	dpvs(this->name);
	dpv(this->token);
	
	EXIT;
	return this;
	#endif
}

