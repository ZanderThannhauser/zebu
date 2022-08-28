
#if 0
#include "../ANY.h"

#include "after_highest.h"

const enum tokenizer_state production_after_highest_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	#include "../fragments/skip_comments.h"
	
	// highest:
		// hashtag:
		#include "../fragments/hashtag.h"
		
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
		#include "../fragments/identifier.h"
		
		// string literal:
		#include "../fragments/string_literal.h"
		
		// character literal:
		#include "../fragments/character_literal.h"
	
	// suffixes:
		// plus:
		[ts_start]['+'] = ts_after_plus,
			[ts_after_plus][ANY] = ts_plus,
		// asterisk
		[ts_start]['*'] = ts_after_asterisk,
			[ts_after_asterisk][ANY] = ts_asterisk,
		// qmark
		[ts_start]['?'] = ts_after_qmark,
			[ts_after_qmark][ANY] = ts_qmark,
	
	// subroot:
		// percent:
		[ts_start]['%'] = ts_after_percent,
			[ts_after_percent][ANY] = ts_percent,
	
	// or:
		// vertical bar:
		[ts_start]['|'] = ts_after_vertical_bar,
			[ts_after_vertical_bar][ANY] = ts_vertical_bar,
	
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




















#endif
