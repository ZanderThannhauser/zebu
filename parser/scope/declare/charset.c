
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/charset/new.h>

#include "../struct.h"

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
	
	avl_insert(this->layer->charsets, new_named_charset(name, charset));
	
	EXIT;
}



















