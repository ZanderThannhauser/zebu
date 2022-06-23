
#include <debug.h>

#include <avl/safe_insert.h>

#include <memory/sstrndup.h>

/*#include "../node/new.h"*/
#include "../struct.h"

#include "../private/append_prefix.h"

#include "../named/token/new.h"

#include "../named/name/new.h"

#include "token.h"

void scope_declare_token(
	struct scope* this,
	char* name,
	struct regex* token)
{
	ENTER;
	
	dpvs(name);
	
	size_t old_len = this->prefix.n;
	
	private_scope_append_prefix(this, name);
	
	char* full_name = sstrndup(this->prefix.chars, this->prefix.n);
	
	dpvs(full_name);
	
	safe_avl_insert(&this->tokens, new_named_token(full_name, token));
	
	safe_avl_insert(&this->layer->tokens, new_named_name(name, full_name));
	
	this->prefix.n = old_len;
	
	EXIT;
}











