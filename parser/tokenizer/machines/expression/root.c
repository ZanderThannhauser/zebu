
#include "../ANY.h"
#include "root.h"

const enum tokenizer_state expression_root_machine[number_of_tokenizer_states][256] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// highest:
		// open sqaure:
		[ts_start]['['] = ts_after_osquare,
			[ts_after_osquare][ANY] = ts_osquare,
		
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
		
		// identifier:
		[ts_start]['a' ... 'z'] = ts_reading_identifier,
			[ts_reading_identifier][ANY] = ts_identifier,
			[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
			[ts_reading_identifier]['_'] = ts_reading_identifier,
		
		// string literal:
		[ts_start]['\"'] = ts_reading_string_literal,
			[ts_reading_string_literal][ANY] = ts_reading_string_literal,
			[ts_reading_string_literal]['\"'] = ts_read_string_literal,
				[ts_read_string_literal][ANY] = ts_string_literal,
		
		// character literal:
		[ts_start]['\''] = ts_read_character_literal1,
			[ts_read_character_literal1][ANY] = ts_read_character_literal2,
			[ts_read_character_literal1]['\\'] = ts_read_character_escape,
				[ts_read_character_escape]['\\'] = ts_read_character_literal2,
				[ts_read_character_escape]['n'] = ts_read_character_literal2,
				[ts_read_character_escape]['\"'] = ts_read_character_literal2,
			[ts_read_character_literal2]['\''] = ts_read_character_literal3,
			[ts_read_character_literal3][ANY] = ts_character_literal,
		
		// dot:
		[ts_start]['.'] = ts_after_dot,
			[ts_after_dot][ANY] = ts_dot,
	
	// prefixes:
		// exclamation mark:
		[ts_start]['!'] = ts_after_emark,
			[ts_after_emark][ANY] = ts_emark,
	
	
};





















