
#include "token.h"
#include "token_names.h"

const char* token_names[number_of_tokens] = {
	// EOF:
	[t_EOF] = "<EOF>",
	
	// symbols:
	[t_dot] = ".",
	[t_vbar] = "|",
	[t_plus] = "+",
	[t_colon] = ":",
	[t_minus] = "-",
	[t_comma] = ",",
	[t_emark] = "!",
	[t_qmark] = "?",
	[t_caret] = "^",
	[t_percent] = "%",
	[t_asterisk] = "*",
	[t_ampersand] = "&",
	[t_gravemark] = "`",
	[t_semicolon] = ";",
	
	// brackets:
	[t_oparen] = "(",
	[t_cparen] = ")",
	[t_osquare] = "[",
	[t_csquare] = "]",
	[t_ocurly] = "{",
	[t_ccurly] = "}",
	
	// literals:
	[t_octal_literal] = "<octal-literal>",
	[t_string_literal] = "<string-literal>",
	[t_decimal_literal] = "<decimal-literal>",
	[t_character_literal] = "<character-literal>",
	[t_hexadecimal_literal] = "<hexadecimal-literal>",
	
	// identifier:
	[t_identifier] = "<identifier>",
	[t_absolute_path] = "<include-path>",
	[t_array_hashtag] = "#hashtag[]",
	[t_scalar_hashtag] = "#hashtag",
};

