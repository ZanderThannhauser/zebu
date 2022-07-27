
#include "../ANY.h"
#include "after_highest.h"

const enum tokenizer_state expression_after_highest_machine[number_of_tokenizer_states][256] = {
	
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
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
		
		// open sqaure:
		[ts_start]['['] = ts_after_osquare,
			[ts_after_osquare][ANY] = ts_osquare,
		
		// fragment name:
		[ts_start]['a' ... 'z'] = ts_reading_fragment,
			[ts_reading_fragment][ANY] = ts_fragment,
			[ts_reading_fragment]['a' ... 'z'] = ts_reading_fragment,
			[ts_reading_fragment]['_'] = ts_reading_fragment,
		
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
	
	// suffixes:
		// question mark:
		[ts_start]['?'] = ts_after_qmark,
			[ts_after_qmark][ANY] = ts_qmark,
		
		// plus:
		[ts_start]['+'] = ts_after_plus,
			[ts_after_plus][ANY] = ts_plus,
		
		// asterisk:
		[ts_start]['*'] = ts_after_asterisk,
			[ts_after_asterisk][ANY] = ts_asterisk,
		
		// ocurly:
		[ts_start]['{'] = ts_after_ocurly,
			[ts_after_ocurly][ANY] = ts_ocurly,
	
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





















