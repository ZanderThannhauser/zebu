
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
	struct unsignedset* whitespace,
	struct unsignedset* tokens)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &trie);
	
	if (node)
	{
		struct stateinfo_node* ele = node->item;
		
		unsignedset_update(ele->whitespace, whitespace);
		
		unsignedset_update(ele->tokens, tokens);
		
		EXIT;
		return NULL;
	}
	else
	{
		struct stateinfo_node* node = new_stateinfo_node(trie, whitespace, tokens);
		
		avl_insert(this->tree, node);
		
		EXIT;
		return node;
	}
}











