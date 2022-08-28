
#include <debug.h>

#include <assert.h>

#include <stddef.h>

#include <avl/insert.h>
#include <avl/search.h>

/*#include <set/of_regexes/new.h>*/
/*#include <set/of_regexes/add.h>*/

/*#include <set/of_tokens/struct.h>*/
/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/foreach.h>*/
/*#include <set/of_tokens/add.h>*/

/*#include <set/of_tokensets/add.h>*/

#ifdef DEBUGGING
/*#include <set/of_tokensets/struct.h>*/
/*#include <set/of_tokens/to_string.h>*/
#endif

/*#include <set/of_tokensets/new.h>*/

#include "../state/free.h"

#include "../struct.h"

#include "../lookup/id_to_dfa.h"

#include "node/struct.h"
#include "node/new.h"

#include "dfas_to_dfa.h"
#include "build_tokenizer.h"

struct tokensetset* lex_build_tokenzer(
	struct lex_state** outgoing,
	struct lex* this,
	struct tokenset* token_ids)
{
	struct tokensetset* retval;
	ENTER;
	
	TODO;
	#if 0
	// check cache
	struct avl_node_t* cache_node = avl_search(this->tokenizer.cache, &token_ids);
	
	if (cache_node)
	{
		// we've built this tokenizer before, what did we say last time?
		
		struct build_tokenizer_node* node = cache_node->item;
		
		*outgoing = node->start;
		
		// return start state, and set of set of tokens
		retval = node->matches;
	}
	else
	{
		// build dfa of all tokens' dfas
		#ifdef WITH_ARENAS
		struct regexset* starts = new_regexset(arena);
		#else
		struct regexset* starts = new_regexset();
		#endif
		
		#ifdef WITH_ARENAS
		retval = new_tokensetset(arena);
		#else
		retval = new_tokensetset();
		#endif
		
		tokenset_foreach(token_ids, ({
			void runme(unsigned token) {
				regexset_add(starts, lex_id_to_dfa(this, token));
			}
			runme;
		}));
		
		#ifdef WITH_ARENAS
		struct lex_state* new_state = dfas_to_dfa(arena, retval, starts);
		#else
		struct lex_state* new_state = dfas_to_dfa(retval, starts);
		#endif
		
		dpv(new_state);
		dpv(retval->n);
		
		#ifdef WITH_ARENAS
		avl_insert(this->tokenizer.cache, new_build_tokenizer_node(arena, token_ids, retval, new_state));
		#else
		avl_insert(this->tokenizer.cache, new_build_tokenizer_node(token_ids, retval, new_state));
		#endif
		
		*outgoing = new_state;
	}
	
	EXIT;
	return retval;
	#endif
}












