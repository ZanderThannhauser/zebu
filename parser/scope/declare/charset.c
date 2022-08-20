
#include <debug.h>

#include <avl/safe_insert.h>

/*#include <memory/sstrndup.h>*/

#include "../struct.h"

/*#include "../private/append_prefix.h"*/

#include <named/charset/new.h>

/*#include <named/name/new.h>*/

#include "charset.h"

void scope_declare_charset(
	struct scope* this,
	char* name,
	struct charset* charset)
{
	ENTER;
	
	dpvs(name);
	
	dpv(charset);
	
	assert(this->layer);
	
	safe_avl_insert(this->layer->charsets, new_named_charset(name, charset));
	
	EXIT;
}




















