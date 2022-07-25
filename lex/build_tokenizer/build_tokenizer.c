
#include <avl/search.h>

#include <debug.h>

#include <assert.h>

#include <stddef.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/foreach.h>

#include "../struct.h"
#include "../lookup/id_to_dfa.h"

#include "build_tokenizer.h"

struct regex* lex_build_tokenzer(
	struct lex* this,
	struct tokenset* token_ids)
{
	ENTER;
	
	// check cache
	struct avl_node_t* cache_node = avl_search(this->tokenset_to_tokenizer, &token_ids);
	
	if (cache_node)
	{
		// we've built this tokenizer before, what did we say last time?
		// return start state, and set of set of tokens
		TODO;
	}
	else
	{
		// build dfa of all tokens' dfas
			// lookup dfas for each id
		{
			TODO;
			#if 0
			size_t i = 0, n = token_ids->n;
			struct regex* (*starts)[n] = smalloc(sizeof(*starts));
			
			tokenset_foreach(token_ids, ({
				void runme(unsigned token) {
					dpv(token);
					(*starts)[i++] = lex_id_to_dfa(this, token);
				}
				runme;
			}));
			
			struct regex* new_start = dfas_to_dfa(*starts, n);
			
			TODO;
			
			free(starts);
			#endif
		}
		
		// iterate through states, possibly adding to tree
		// clone/simplifiy dfa
		TODO;
		
		// add new tokenizer to cache
		TODO;
		
		// free original dfa
		TODO;
	}
	
	EXIT;
}

// import machines

// lookup = dict()  # fingers -> state;

// patches = dict() # set(token ids) -> token_ids

// def build_tokenizer(token_ids):
	// if token_ids in cached:
		// return cached[token_ids];
	// else:
		// fingers = dict() # index -> state
		
		// for i, id in enumerate(token_ids):
			// fingers[machines[id]] = i;
			
		// def helper(fingers):
			// if list(fingers.values()) in lookup:
				//
			// else:
				// state = new state();
				// lookup[] = state;
				// accepting = set(f for f in fingers if f.is_accepting);
				// match len(accepting):
					// case 0: pass
					// case 1: state.is_accepting = true
					// case _:
						// ids = set(token_ids[fingers[a]] for a in accepting);
						// if ids in patches:
							//
						// else:
							// patches[ids] = counter;
							// counter += 1;
				
				// transitions = set();
				// for f in fingers:
					// transitions.update(s.transitions);
				// while transitions:
					// value = transitions.pop();
					// new_fingers = dict();
					// for f, i in fingers.items():
						// if value in f.transitions:
							// new_fingers[f.transitions[value]] = i;
					// state[value] = helper(new_fingers);

		// start = helper(fingers);














