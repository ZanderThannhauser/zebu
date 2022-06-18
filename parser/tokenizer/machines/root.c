
#include "ANY.h"
#include "root.h"

enum tokenizer_state root_machine[number_of_tokenizer_states][256] = {
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// directives:
	[ts_start]['%'] = ts_after_percent,
		[ts_after_percent][    ANY    ] = ts_directive,
		[ts_after_percent]['a' ... 'z'] = ts_after_percent,
	
	// fragments:
	[ts_start]['`'] = ts_reading_fragment,
		[ts_reading_fragment][ANY] = ts_reading_fragment,
		[ts_reading_fragment]['`'] = ts_read_fragment,
			[ts_read_fragment][ANY] = ts_fragment,
	
	// identifier (start of grammar rule):
	[ts_start]['a' ... 'z'] = ts_reading_identifier,
		[ts_reading_identifier][ANY] = ts_identifier,
		[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
};

