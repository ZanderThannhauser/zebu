
#include <debug.h>

#include <assert.h>

#include <stddef.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <set/unsigned/foreach.h>

#include <set/unsignedset/inc.h>

#include "../state/free.h"

#include "../struct.h"

#include "../id_to_dfa.h"

#include "node/struct.h"
#include "node/new.h"

#include "dfas_to_dfa.h"
#include "build_tokenizer.h"

struct unsignedsetset* lex_build_tokenzer(
	struct lex* this,
	struct lex_state** outgoing,
	struct unsignedset* token_ids)
{
	ENTER;
	
	// check cache
	struct avl_node_t* cache_node = avl_search(this->tokenizer_cache, &token_ids);
	
	if (cache_node)
	{
		// we've built this tokenizer before, what did we say last time?
		
		struct build_tokenizer_node* node = cache_node->item;
		
		*outgoing = node->start;
		
		EXIT
		return inc_unsignedsetset(node->matches);
	}
	else
	{
		struct ptrset* starts = new_ptrset();
		
		unsignedset_foreach(token_ids, ({
			void runme(unsigned token) {
				ptrset_add(starts, lex_id_to_dfa(this, token));
			}
			runme;
		}));
		
		struct unsignedsetset* accepts = dfas_to_dfa(outgoing, starts);
		
		avl_insert(this->tokenizer_cache, new_build_tokenizer_node(token_ids, accepts, *outgoing));
		
		free_ptrset(starts);
		
		EXIT
		return accepts;
	}
}


















