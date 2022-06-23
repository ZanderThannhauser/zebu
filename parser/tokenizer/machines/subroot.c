
#include "ANY.h"
#include "root.h"

enum tokenizer_state subroot_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// charset:
	[ts_start]['['] = ts_reading_charset,
		[ts_reading_charset][ANY] = ts_reading_charset,
		[ts_reading_charset][']'] = ts_read_charset,
			[ts_read_charset][ANY] = ts_charset,
	
	// fragments:
	[ts_start]['`'] = ts_reading_fragment,
		[ts_reading_fragment][ANY] = ts_reading_fragment,
		[ts_reading_fragment]['`'] = ts_read_fragment,
			[ts_read_fragment][ANY] = ts_fragment,
	
	// identifier (start of grammar rule):
	[ts_start]['a' ... 'z'] = ts_reading_identifier,
		[ts_reading_identifier][ANY] = ts_identifier,
		[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
	
	// end:
		// colon:
		[ts_start][':'] = ts_after_colon,
			[ts_after_colon][ANY] = ts_colon,
		
};

