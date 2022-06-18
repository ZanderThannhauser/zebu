
#include "ANY.h"
#include "semicolon.h"

enum tokenizer_state semicolon_machine[number_of_tokenizer_states][256] = {
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// semicolon:
	[ts_start][';'] = ts_after_semicolon,
		[ts_after_semicolon][ANY] = ts_semicolon,
	
};

