
#include "../ANY.h"

#include "include.h"

enum tokenizer_state include_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	#include "../fragments/relative_path.h"
	
	#include "../fragments/absolute_path.h"
};
