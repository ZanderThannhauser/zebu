
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <string/struct.h>
#include <string/new.h>
#include <string/free.h>

#include <named/gegex/new.h>

#include <avl/insert.h>

#include "../struct.h"

#include "grammar.h"

void scope_declare_grammar(
	struct scope* this,
	struct string* name,
	struct gegex* grammar)
{
	ENTER;
	
	if (this->prefix.n)
	{
		char* full = malloc(this->prefix.n + 1 + name->len + 1), *m = full;
		
		memcpy(full, this->prefix.chars, this->prefix.n), m += this->prefix.n;
		
		*m++ = '$';
		
		memcpy(m, name->chars, name->len), m += name->len;
		
		*m = '\0';
		
		dpvs(full);
		
		struct string* full_name = new_string_without_copy(full);
		
		avl_insert(this->grammar, new_named_gegex(full_name, grammar));
		
		free_string(full_name);
	}
	else
	{
		avl_insert(this->grammar, new_named_gegex(name, grammar));
	}
	
	EXIT;
}














