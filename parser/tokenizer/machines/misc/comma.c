
#include "../ANY.h"

#include "comma.h"

enum tokenizer_state comma_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/comma.h"
};
