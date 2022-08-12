
#include "../ANY.h"

#include "colon.h"

enum tokenizer_state colon_machine[number_of_tokenizer_states][256] = {
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// colon:
	[ts_start][':'] = ts_after_colon,
		[ts_after_colon][ANY] = ts_colon,
	
};

