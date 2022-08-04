
#include <debug.h>

#include <avl/safe_insert.h>

#include <memory/sstrndup.h>

#include "../struct.h"

#include "../private/append_prefix.h"

#include <named/grammar/new.h>

#include <named/name/new.h>

#include "grammar.h"

void scope_declare_grammar(
	struct scope* this,
	char* name,
	struct gegex* grammar)
{
	ENTER;
	
	dpvs(name);
	
	size_t old_len = this->prefix.n;
	
	private_scope_append_prefix(this, name);
	
	char* full_name = sstrndup(this->prefix.chars, this->prefix.n);
	
	dpvs(full_name);
	
	safe_avl_insert(this->grammar, new_named_grammar(full_name, grammar));
	
	safe_avl_insert(this->layer->grammar, new_named_name(name, full_name));
	
	this->prefix.n = old_len;
	
	EXIT;
}












