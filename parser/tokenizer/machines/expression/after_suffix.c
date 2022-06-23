
#include "../ANY.h"
#include "after_suffix.h"

enum tokenizer_state expression_after_suffix_machine[number_of_tokenizer_states][256] = {
	
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
		[ts_start]['['] = ts_after_osqaure,
			[ts_after_osqaure][ANY] = ts_osqaure,
		
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
	
		// fragment name:
		[ts_start]['a' ... 'z'] = ts_reading_fragment,
			[ts_reading_fragment][ANY] = ts_fragment,
			[ts_reading_fragment]['a' ... 'z'] = ts_reading_fragment,
		
		// string literal:
		[ts_start]['\"'] = ts_reading_string_literal,
			[ts_reading_string_literal][ANY] = ts_reading_string_literal,
			[ts_reading_string_literal]['\"'] = ts_read_string_literal,
				[ts_read_string_literal][ANY] = ts_string_literal,
		
		// dot:
		[ts_start]['.'] = ts_after_dot,
			[ts_after_dot][ANY] = ts_dot,
		
	// prefixes:
		// exclamation mark:
		[ts_start]['!'] = ts_after_emark,
			[ts_after_emark][ANY] = ts_emark,
	
	// and operator:
	[ts_start]['&'] = ts_after_ampersand,
		[ts_after_ampersand][ANY] = ts_ampersand,
	
	// or operator:
	[ts_start]['|'] = ts_after_vertical_bar,
		[ts_after_vertical_bar][ANY] = ts_vertical_bar,
	
	// end of expression:
		// close paren:
		[ts_start][')'] = ts_after_cparen,
			[ts_after_cparen][ANY] = ts_cparen,
		
		// semicolon
		[ts_start][';'] = ts_after_semicolon,
			[ts_after_semicolon][ANY] = ts_semicolon,
		
		// gravemark
		[ts_start]['`'] = ts_after_gravemark,
			[ts_after_gravemark][ANY] = ts_gravemark,
};





















