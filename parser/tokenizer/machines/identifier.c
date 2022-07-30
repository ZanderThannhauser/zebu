
#include "ANY.h"
#include "identifier.h"

enum tokenizer_state identifier_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,

	// identifier:
	[ts_start]['a' ... 'z'] = ts_reading_identifier,
	[ts_start]['A' ... 'Z'] = ts_reading_identifier,
		[ts_reading_identifier][ANY] = ts_identifier,
		[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
		[ts_reading_identifier]['A' ... 'Z'] = ts_reading_identifier,
		[ts_reading_identifier]['_'] = ts_reading_identifier,
	
};





















