
#include "../ANY.h"

#include "semicolon.h"

enum tokenizer_state semicolon_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// semicolon:
	[ts_start][';'] = ts_after_semicolon,
		[ts_after_semicolon][ANY] = ts_semicolon,
	
};

