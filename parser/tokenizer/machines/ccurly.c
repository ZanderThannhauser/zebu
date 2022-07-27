
#include "ANY.h"
#include "ccurly.h"

enum tokenizer_state ccurly_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// ccurly:
	[ts_start]['}'] = ts_after_ccurly,
		[ts_after_ccurly][ANY] = ts_ccurly,
	
};

