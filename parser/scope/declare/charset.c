
#include <debug.h>

#include <avl/safe_insert.h>

#include <memory/sstrndup.h>

#include "../struct.h"

#include "../private/append_prefix.h"

#include <named/charset/new.h>

#include <named/name/new.h>

#include "charset.h"

void scope_declare_charset(
	struct scope* this,
	char* name,
	struct charset* charset)
{
	ENTER;
	
	dpvs(name);
	
	size_t old_len = this->prefix.n;
	
	private_scope_append_prefix(this, name);
	
	char* full_name = sstrndup(this->prefix.chars, this->prefix.n);
	
	dpvs(full_name);
	
	safe_avl_insert(this->charsets, new_named_charset(full_name, charset));
	
	safe_avl_insert(this->layer->charsets, new_named_name(name, full_name));
	
	this->prefix.n = old_len;
	
	EXIT;
}




















