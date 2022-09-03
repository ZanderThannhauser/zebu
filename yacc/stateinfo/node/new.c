
#include <debug.h>

#include "struct.h"
#include "new.h"

struct stateinfo_node* new_stateinfo_node(
	struct trie* trie,
	struct unsignedset* lookahead // you're givin this to me
) {
	ENTER;
	
	struct stateinfo_node* this = smalloc(sizeof(*this));
	
	this->trie = trie;
	
	this->lookahead = lookahead;
	
	EXIT;
	return this;
}

