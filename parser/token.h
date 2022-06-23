
#ifndef ENUM_TOKEN
#define ENUM_TOKEN

enum token
{
	t_error,
	
	t_EOF,
	
	// symbols:
	t_colon,
	t_oparen,
	t_osquare,
	t_semicolon,
	t_dot,
	t_plus,
	t_emark,
	t_qmark,
	t_asterisk,
	t_ocurly,
	t_gthan,
	t_gthan_eq,
	t_vertical_bar,
	t_lthan,
	t_lthan_eq,
	t_equal_to,
	t_ampersand,
	t_tilda,
	t_not_equal_to,
	t_hypen,
	t_caret,
	t_gravemark,
	t_cparen,
	t_csquare,
	
	t_ellipsis,
	
	t_character_literal,
	
	// strings:
	t_string_literal,
	t_absolute_path,
	t_relative_path,
	t_fragment,
	t_charset,
	t_identifier,
	
	t_directive,
	
	number_of_tokens,
};

#endif
