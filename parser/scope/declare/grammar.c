
#include <debug.h>

#include <named/grammar/new.h>

/*#include <named/name/new.h>*/

#include "../struct.h"

#include "../private/append_prefix.h"

#include "grammar.h"

void scope_declare_grammar(
	struct scope* this,
	char* name,
	struct gegex* grammar)
{
	ENTER;
	
	dpvs(name);
	
	TODO;
	#if 0
	size_t old_len = this->prefix.n;
	
	private_scope_append_prefix(this, name);
	
	char* full_name = sstrndup(this->prefix.chars, this->prefix.n);
	
	dpvs(full_name);
	
	safe_avl_insert(this->grammar, new_named_grammar(full_name, grammar));
	
	this->prefix.n = old_len;
	#endif
	
	EXIT;
}












