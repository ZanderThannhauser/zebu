
#ifndef ENUM_TOKEN
#define ENUM_TOKEN

enum token
{
	t_error,
	
	t_EOF,
	
	// symbols:
	t_dot,
	t_vbar,
	t_plus,
	t_colon,
	t_comma,
	t_minus,
	t_emark,
	t_qmark,
	t_caret,
	t_percent,
	t_asterisk,
	t_gravemark,
	t_ampersand,
	t_semicolon,
	
	// brackets:
	t_oparen, t_cparen,
	t_osquare, t_csquare,
	t_ocurly, t_ccurly,
	
	// literals:
	t_octal_literal,
	t_string_literal,
	t_decimal_literal,
	t_character_literal,
	t_hexadecimal_literal,
	
	// identifers:
	t_identifier,
	t_array_hashtag,
	t_scalar_hashtag,
	
	number_of_tokens,
};

#endif
















