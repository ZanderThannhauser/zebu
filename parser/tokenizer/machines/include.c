
#include "ANY.h"
#include "include.h"

enum tokenizer_state include_machine[number_of_tokenizer_states][256] = {
	
	// EOF:
	[ts_start][ 0 ] = ts_EOF,
	
	#include "fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// relative path:
	[ts_start]['\"'] = ts_reading_relpath_literal,
		[ts_reading_relpath_literal][ ANY] = ts_reading_relpath_literal,
		[ts_reading_relpath_literal]['\"'] = ts_read_relpath_literal,
			[ts_read_relpath_literal][ANY] = ts_relative_path,
	
	// absolute path:
	[ts_start]['<'] = ts_reading_abspath_literal,
		[ts_reading_abspath_literal][ANY] = ts_reading_abspath_literal,
		[ts_reading_abspath_literal]['>'] = ts_read_abspath_literal,
			[ts_read_abspath_literal][ANY] = ts_absolute_path,
	
};

