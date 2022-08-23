
#include <assert.h>

#include <debug.h>

/*#include <memory/sstrndup.h>*/
#include <avl/insert.h>

/*#include "../private/append_prefix.h"*/

#include <named/token/new.h>

/*#include <named/name/new.h>*/

#include "../struct.h"

#include "fragment.h"

void scope_declare_fragment(
	struct scope* this,
	char* name,
	struct regex* token)
{
	ENTER;
	
	dpvs(name);
	dpv(token);
	
	assert(this->layer);
	
	#ifdef WITH_ARENAS
	avl_insert(this->layer->fragments, new_named_token(this->layer->arena, name, token));
	#else
	avl_insert(this->layer->fragments, new_named_token(name, token));
	#endif
	
	EXIT;
}











