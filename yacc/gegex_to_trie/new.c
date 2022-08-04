
#include <debug.h>

#include "struct.h"
#include "new.h"

struct gegex_to_trie* new_gegex_to_trie(
	struct gegex* gegex,
	const char* trie)
{
	ENTER;
	
	struct gegex_to_trie* this = smalloc(sizeof(*this));
	
	this->gegex = gegex;
	this->trie = trie;
	
	EXIT;
	return this;
}

