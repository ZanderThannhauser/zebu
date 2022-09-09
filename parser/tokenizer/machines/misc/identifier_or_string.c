
#if 0
#include "../ANY.h"

#include "identifier_or_string.h"

enum tokenizer_state identifier_or_string_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
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
	
	// string literal:
	[ts_start]['\"'] = ts_reading_string_literal,
		[ts_reading_string_literal][ANY] = ts_reading_string_literal,
		[ts_reading_string_literal]['\"'] = ts_read_string_literal,
			[ts_read_string_literal][ANY] = ts_string_literal,
	
};




















#endif