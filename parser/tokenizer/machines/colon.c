
#include "ANY.h"
#include "colon.h"

enum tokenizer_state colon_machine[number_of_tokenizer_states][128] = {
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// colon:
	[ts_start][':'] = ts_after_colon,
		[ts_after_colon][ANY] = ts_colon,
	
};

