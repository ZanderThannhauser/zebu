
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	char* name,
	struct charset* charset)
{
	ENTER;
	
	TODO;
	#if 0
	struct named_charset* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->charset = charset;
	
	dpvs(this->name);
	dpv(this->charset);
	
	EXIT;
	return this;
	#endif
}

