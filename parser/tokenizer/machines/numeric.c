
#include "ANY.h"
#include "numeric.h"

enum tokenizer_state numeric_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// numeric:
	[ts_start]['0' ... '9'] = ts_reading_numeric,
		[ts_reading_numeric][ANY] = ts_numeric,
		[ts_reading_numeric]['0' ... '9'] = ts_reading_numeric,
	
};

