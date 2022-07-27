
#include "ANY.h"
#include "comma.h"

enum tokenizer_state comma_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// comma:
	[ts_start][','] = ts_after_comma,
		[ts_after_comma][ANY] = ts_comma,
	
};

