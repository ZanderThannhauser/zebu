
#include "../ANY.h"

#include "colon.h"

enum tokenizer_state colon_machine[number_of_tokenizer_states][256] =
{
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	#include "../fragments/colon.h"
	
};
