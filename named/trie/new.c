
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_trie* new_named_trie(
	struct string* name,
	struct trie* trie)
{
	ENTER;
	
	dpvs(name);
	
	struct named_trie* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->trie = trie;
	
	EXIT;
	return this;
}

