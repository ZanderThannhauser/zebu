
#include "../ANY.h"

#include "after_highest.h"

enum tokenizer_state charset_after_highest_machine[number_of_tokenizer_states][256] = {
	
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
		// character literal:
		[ts_start]['\''] = ts_read_character_literal1,
			[ts_read_character_literal1][ANY] = ts_read_character_literal2,
			[ts_read_character_literal1]['\\'] = ts_read_character_escape,
				[ts_read_character_escape]['\\'] = ts_read_character_literal2,
				[ts_read_character_escape]['n'] = ts_read_character_literal2,
			[ts_read_character_literal2]['\''] = ts_read_character_literal3,
			[ts_read_character_literal3][ANY] = ts_character_literal,
		
		// identifier:
		[ts_start]['a' ... 'z'] = ts_reading_identifier,
			[ts_reading_identifier][ANY] = ts_identifier,
			[ts_reading_identifier]['a' ... 'z'] = ts_reading_identifier,
		
		// open paren:
		[ts_start]['('] = ts_after_oparen,
			[ts_after_oparen][ANY] = ts_oparen,
		
	// prefixes:
		// tilda:
		[ts_start]['~'] = ts_after_tilda,
			[ts_after_tilda][ANY] = ts_tilda,
	
	// range:
		// hypen:
		[ts_start]['-'] = ts_after_hypen,
			[ts_after_hypen][ANY] = ts_hypen,
	
	// intersect:
		// ampersand:
		[ts_start]['&'] = ts_after_ampersand,
			[ts_after_ampersand][ANY] = ts_ampersand,
	
	// symmetric difference:
		// caret:
		[ts_start]['^'] = ts_after_caret,
			[ts_after_caret][ANY] = ts_caret,
	
	// union:
		// vertical bar:
		[ts_start]['|'] = ts_after_vertical_bar,
			[ts_after_vertical_bar][ANY] = ts_vertical_bar,
		// comma:
		[ts_start][','] = ts_after_comma,
			[ts_after_comma][ANY] = ts_comma,
	
	// end of expression:
		// semicolon:
		[ts_start][';'] = ts_after_semicolon,
			[ts_after_semicolon][ANY] = ts_semicolon,
		// close paren:
		[ts_start][')'] = ts_after_cparen,
			[ts_after_cparen][ANY] = ts_cparen,
		// close square:
		[ts_start][']'] = ts_after_csquare,
			[ts_after_csquare][ANY] = ts_csqaure,
	
};





















