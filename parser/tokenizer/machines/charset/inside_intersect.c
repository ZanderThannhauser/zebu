
#if 0
#include "../ANY.h"

#include "root.h"

const enum tokenizer_state charset_inside_intersect_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// highest:
		// character literal:
		[ts_start]['\''] = ts_read_character_literal1,
			[ts_read_character_literal1][ANY] = ts_read_character_literal2,
			[ts_read_character_literal1]['\\'] = ts_read_character_escape,
				[ts_read_character_escape]['\\'] = ts_read_character_literal2,
				[ts_read_character_escape]['n'] = ts_read_character_literal2,
				[ts_read_character_escape]['t'] = ts_read_character_literal2,
				[ts_read_character_escape]['\''] = ts_read_character_literal2,
				[ts_read_character_escape]['\"'] = ts_read_character_literal2,
			[ts_read_character_literal2]['\''] = ts_read_character_literal3,
			[ts_read_character_literal3][ANY] = ts_character_literal,
		
		// identifier:
		[ts_start]['a' ... 'z'] = ts_reading_identifier,
			[ts_reading_identifier][ANY] = ts_identifier,
			[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
			[ts_reading_identifier]['_'] = ts_reading_identifier,
		
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
		
	// prefixes:
		// set not:
		[ts_start]['~'] = ts_after_tilda,
			[ts_after_tilda][ANY] = ts_tilda,
	
	
};




















#endif
