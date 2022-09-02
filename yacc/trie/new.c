
#include <debug.h>

#include "struct.h"
#include "new.h"

struct trie* new_trie()
{
	ENTER;
	
	struct trie* this = smalloc(sizeof(*this));
	
	EXIT;
	return this;
}

