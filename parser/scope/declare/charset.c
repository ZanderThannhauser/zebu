
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/charset/new.h>

#include "../struct.h"

#include "charset.h"

void scope_declare_charset(
	struct scope* this,
	struct string* name,
	charset_t charset)
{
	ENTER;
	
	assert(this->layer);
	
	avl_insert(this->layer->charsets, new_named_charset(name, charset));
	
	EXIT;
}



















