
#include <debug.h>

#include "build_tokenizer.h"

static struct regex* dfas_to_dfa(
	struct regex* fingers, size_t n)
{
	ENTER;
	TODO;
	EXIT;
}

struct regex* lex_build_tokenzer(
	struct tokenset* token_ids)
{
	ENTER;
	
	// check cache
	TODO;
	
	// build dfa of all tokens' dfas
		// lookup dfas for each id
	TODO;
	
	// iterate through states, possibly adding to lookup
	TODO;
	
	// clone/simplifiy dfa
	TODO;
	
	// free original dfa
	TODO;
	
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













