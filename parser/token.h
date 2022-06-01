
#ifndef ENUM_TOKEN
#define ENUM_TOKEN

enum token
{
	t_error,
	
	t_EOF,
	
	// symbols:
	t_colon,
	t_oparen,
	t_semicolon,
	t_dot,
	t_plus,
	t_emark,
	t_qmark,
	t_asterisk,
	t_ocurly,
	
	t_ellipsis,
	
	// strings:
	t_string_literal,
	t_absolute_path,
	t_relative_path,
	t_fragment,
	t_identifier,
	
	t_directive,
	
	number_of_tokens,
};

#endif
