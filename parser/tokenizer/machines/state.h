
#ifndef ENUM_TOKENIZER_STATE
#define ENUM_TOKENIZER_STATE

enum tokenizer_state
{
	ts_error,
	
	// tokens:
	ts_EOF,
	
	// symbols:
	ts_plus,
	ts_lthan,
	ts_gthan,
	ts_emark,
	ts_qmark,
	ts_colon,
	ts_and,
	ts_oparen,
	ts_cparen,
	ts_osqaure,
	ts_csqaure,
	ts_asterisk,
	ts_lthan_eq,
	ts_gthan_eq,
	ts_equal_to,
	ts_or,
	ts_dot,
	ts_ellipsis,
	ts_not_equal_to,
	ts_semicolon,
	ts_gravemark,
	
	// strings:
	ts_string_literal,
	ts_absolute_path,
	ts_relative_path,
	ts_fragment,
	
	// keywords/misc:
	ts_directive,
	ts_if,
	ts_else,
	
	ts_start,
	
	// skip comments:
	ts_skipping_comment,
	
	// symbols:
	ts_after_plus,
	ts_after_colon,
	ts_after_slash,
	ts_after_emark,
	ts_after_emark_eq,
	ts_after_lthan,
	ts_after_gthan,
	ts_after_qmark,
	ts_after_equal,
	ts_after_oparen,
	ts_after_cparen,
	ts_after_percent,
	ts_after_equal_to,
	ts_after_and,
	ts_after_or,
	ts_after_dot,
	ts_after_dotdot,
	ts_after_osqaure,
	ts_after_dotdotdot,
	ts_after_lthan_eq,
	ts_after_gthan_eq,
	ts_after_asterisk,
	ts_after_not_equal_to,
	ts_after_semicolon,
	ts_after_gravemark,
	
	// strings:
	ts_reading_string_literal,
	ts_reading_relpath_literal,
	ts_reading_abspath_literal,
	ts_reading_fragment,
	
	ts_read_string_literal,
	ts_read_relpath_literal,
	ts_read_abspath_literal,
	ts_read_fragment,
	
	// keywords:
	ts_after_i,
	ts_after_if,
	ts_after_e,
	ts_after_el,
	ts_after_els,
	ts_after_else,
	
	number_of_tokenizer_states,
};

#endif















