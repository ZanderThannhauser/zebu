

#include "../ANY.h"
#include "ccurly.h"

enum tokenizer_state ccurly_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// ccurly:
	#include "../fragments/ccurly.h"
	
};
