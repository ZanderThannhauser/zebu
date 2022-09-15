
#include <debug.h>

#include <memory/smalloc.h>

#include <set/unsigned/inc.h>

#include "struct.h"
#include "new.h"

struct stateinfo_node* new_stateinfo_node(
	struct trie* trie,
	struct unsignedset* whitespace,
	struct unsignedset* lookaheads
) {
	ENTER;
	
	struct stateinfo_node* this = smalloc(sizeof(*this));
	
	this->trie = trie;
	
	this->whitespace = inc_unsignedset(whitespace);
	
	this->lookaheads = inc_unsignedset(lookaheads);
	
	EXIT;
	return this;
}

