
#include "ANY.h"
#include "expression_after_highest.h"

enum tokenizer_state expression_after_highest_machine[number_of_tokenizer_states][128] = {
	
	// skip whitespace:
	[ts_start][' ' ] = ts_start,
	[ts_start]['\t'] = ts_start,
	[ts_start]['\n'] = ts_start,
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,
	
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
	
	// range:
		// ellipsis:
		[ts_start]['.'] = ts_after_dot,
			[ts_after_dot]['.'] = ts_after_dotdot,
				[ts_after_dotdot]['.'] = ts_after_dotdotdot,
					[ts_after_dotdotdot][ANY] = ts_ellipsis,
	
	// firsts:
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
		
		// prefixes:
			// exclamation mark:
			[ts_start]['!'] = ts_after_emark,
				[ts_after_emark][ANY] = ts_emark,
	
	// compare operators:
		// <, <=:
		[ts_start]['<'] = ts_after_lthan,
			[ts_after_lthan][ANY] = ts_lthan,
			[ts_after_lthan]['='] = ts_after_lthan_eq,
				[ts_after_lthan_eq][ANY] = ts_lthan_eq,
		
		// >, >=:
		[ts_start]['>'] = ts_after_gthan,
			[ts_after_gthan][ANY] = ts_gthan,
			[ts_after_gthan]['='] = ts_after_gthan_eq,
				[ts_after_gthan_eq][ANY] = ts_gthan_eq,
		
		// ==:
		[ts_start]['='] = ts_after_equal,
			[ts_after_equal]['='] = ts_after_equal_to,
				[ts_after_equal_to][ANY] = ts_equal_to,
		
		// !=:
		[ts_start]['!'] = ts_after_emark,
			[ts_after_emark]['='] = ts_after_emark_eq,
				[ts_after_emark_eq][ANY] = ts_not_equal_to,
	
	// and operator:
	[ts_start]['&'] = ts_after_and,
		[ts_after_and][ANY] = ts_and,
	
	// or operator:
	[ts_start]['|'] = ts_after_or,
		[ts_after_or][ANY] = ts_or,
	
	// ternary operator(s?):
		// "if" keyword:
		[ts_start]['i'] = ts_after_i,
			[ts_after_i]['f'] = ts_after_if,
				[ts_after_if][ANY] = ts_if,
		
		// "else" keyword:
		[ts_start]['e'] = ts_after_e,
			[ts_after_e]['l'] = ts_after_el,
				[ts_after_el]['s'] = ts_after_els,
					[ts_after_els]['e'] = ts_after_else,
						[ts_after_else][ANY] = ts_else,
	
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





















