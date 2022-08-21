
#include <debug.h>

/*#include <memory/sstrndup.h>*/

#include "../struct.h"

/*#include "../private/append_prefix.h"*/

#include <named/token/new.h>

/*#include <named/name/new.h>*/

#include "fragment.h"

void scope_declare_fragment(
	struct scope* this,
	char* name,
	struct regex* token)
{
	ENTER;
	
	TODO;
	#if 0
	dpvs(name);
	dpv(token);
	
	assert(this->layer);
	
	safe_avl_insert(this->layer->fragments, new_named_token(name, token));
	#endif
	
	EXIT;
}











