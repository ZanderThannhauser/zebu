
#include "../ANY.h"

#include "comma_or_ccurly.h"

enum tokenizer_state comma_or_ccurly_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/comma.h"
	
	#include "../fragments/ccurly.h"
};
