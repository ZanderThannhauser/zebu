
#include "../ANY.h"

#include "inside_or.h"

const enum tokenizer_state production_inside_subdefinitions_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
	// highest:
		// charset expression:
		[ts_start]['['] = ts_after_osquare,
			[ts_after_osquare][ANY] = ts_osquare,
		
		// token expression:
		[ts_start]['`'] = ts_after_gravemark,
			[ts_after_gravemark][ANY] = ts_gravemark,
		
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
		
		// grammar name:
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
		
	// subroot:
		// percent:
		[ts_start]['%'] = ts_after_percent,
			[ts_after_percent][ANY] = ts_percent,
	
	// end of expression:
		// close paren:
		[ts_start][')'] = ts_after_cparen,
			[ts_after_cparen][ANY] = ts_cparen,
		
		// colon:
		[ts_start][':'] = ts_after_colon,
			[ts_after_colon][ANY] = ts_colon,
		
		// semicolon
		[ts_start][';'] = ts_after_semicolon,
			[ts_after_semicolon][ANY] = ts_semicolon,
};





















