
#include "../ANY.h"

#include "identifier.h"

enum tokenizer_state identifier_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	#include "../fragments/identifier.h"
	
};




















