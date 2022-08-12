
#include "ANY.h"
#include "root.h"

enum tokenizer_state root_machine[number_of_tokenizer_states][256] = {
	
	#include "fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// directives:
	[ts_start]['%'] = ts_after_percent,
		[ts_after_percent][    ANY    ] = ts_directive,
		[ts_after_percent]['a' ... 'z'] = ts_after_percent,
	
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
	[ts_start]['A' ... 'Z'] = ts_reading_identifier,
		[ts_reading_identifier][ANY] = ts_identifier,
		[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
		[ts_reading_identifier]['A' ... 'Z'] = ts_reading_identifier,
		[ts_reading_identifier]['_'] = ts_reading_identifier,
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
};

