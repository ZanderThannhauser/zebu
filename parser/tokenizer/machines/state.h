
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
	ts_tilda,
	ts_colon,
	ts_oparen,
	ts_cparen,
	ts_osquare,
	ts_asterisk,
	ts_ocurly,
	ts_hypen,
	ts_ampersand,
	ts_equal_to,
	ts_vertical_bar,
	ts_caret,
	ts_comma,
	ts_dot,
	ts_ellipsis,
	ts_ccurly,
	ts_semicolon,
	ts_gravemark,
	ts_csquare,
	ts_percent,
	
	ts_character_literal,
	
	// strings:
	ts_bracketed_identifier,
	ts_gravemarked_identifier,
	ts_parenthesised_identifier,
	ts_string_literal,
	ts_absolute_path,
	ts_relative_path,
	ts_numeric_literal,
	ts_identifier,
	
	// keywords/misc:
	ts_directive,
	
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
	ts_after_ocurly,
	ts_after_tilda,
	ts_after_ccurly,
	ts_after_equal_to,
	ts_after_ampersand,
	ts_after_caret,
	ts_after_and,
	ts_after_vertical_bar,
	ts_after_comma,
	ts_after_dot,
	ts_after_dotdot,
	ts_after_osquare,
	ts_after_dotdotdot,
	ts_after_asterisk,
	ts_after_hypen,
	ts_after_semicolon,
	ts_after_gravemark,
	ts_after_csquare,
	
	ts_read_character_literal1,
	ts_read_character_literal2,
	ts_read_character_escape,
	ts_read_character_literal3,
	
	// strings:
	ts_reading_bracketed_identifier,
	ts_reading_gravemarked_identifier,
	ts_reading_parenthesised_identifier,
	ts_reading_numeric_literal,
	ts_reading_string_literal,
	ts_reading_relpath_literal,
	ts_reading_abspath_literal,
	ts_reading_identifier,
	
	ts_read_bracketed_identifier,
	ts_read_gravemarked_identifier,
	ts_read_parenthesised_identifier,
	ts_read_string_literal,
	ts_read_relpath_literal,
	ts_read_abspath_literal,
	
	number_of_tokenizer_states,
};

#endif















