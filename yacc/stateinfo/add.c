
#include <debug.h>

#include "node/new.h"

#include "struct.h"
#include "add.h"

struct stateinfo_node* stateinfo_add(
	struct stateinfo* this,
	struct trie* trie,
	struct unsignedset* lookahead // you're giving this to me
) {
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &trie);
	
	if (node)
	{
		// update lookahead
		TODO;
		
		// free given lookahead
		TODO;
	}
	else
	{
		struct stateinfo_node* node = new_stateinfo_node(trie, lookahead);
		
		avl_insert(this->tree, node);
		
		EXIT;
		return node;
	}
}

