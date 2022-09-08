

#include "../ANY.h"

#include "numeric.h"

enum tokenizer_state numeric_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/numeric_literal.h"
	
};

