
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/charset/new.h>

#include "../struct.h"

#include "charset.h"

void scope_declare_charset(
	struct scope* this,
	struct string* name,
	bool is_complement,
	struct unsignedcharset* charset)
{
	ENTER;
	
	dpv(charset);
	
	assert(this->layer);
	
	avl_insert(this->layer->charsets, new_named_charset(name, is_complement, charset));
	
	EXIT;
}



















