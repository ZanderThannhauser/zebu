

#include "../ANY.h"

#include "numeric_or_ccurly.h"

enum tokenizer_state numeric_or_ccurly_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/numeric_literal.h"
	
	#include "../fragments/ccurly.h"
	
};

