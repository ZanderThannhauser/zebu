
#include <stddef.h>

#include <debug.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <set/unsigned/update.h>
#include <set/unsigned/free.h>

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "add.h"

struct stateinfo_node* stateinfo_add(
	struct stateinfo* this,
	struct trie* trie,
	struct unsignedset* lookaheads // you're giving this to me
) {
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &trie);
	
	if (node)
	{
		struct stateinfo_node* ele = node->item;
		
		unsignedset_update(ele->lookaheads, lookaheads);
		
		free_unsignedset(lookaheads);
		
		EXIT;
		return NULL;
	}
	else
	{
		struct stateinfo_node* node = new_stateinfo_node(trie, lookaheads);
		
		avl_insert(this->tree, node);
		
		EXIT;
		return node;
	}
}

