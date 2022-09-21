
#include "token.h"
#include "token_names.h"

const char* token_names[number_of_tokens] = {
	[t_EOF] = "<EOF>",
	
	// symbols:
	[t_dot] = ".",
	[t_colon] = ":",
	[t_comma] = ",",
	[t_minus] = "-",
	[t_percent] = "%",
	[t_gravemark] = "`",
	[t_semicolon] = ";",
	
	// brackets:
	[t_oparen] = "(",
	[t_cparen] = ")",
	[t_osquare] = "[",
	[t_csquare] = "]",
	
	// literals:
	[t_octal_literal] = "<octal-literal>",
	[t_string_literal] = "<string-literal>",
	[t_decimal_literal] = "<decimal-literal>",
	[t_character_literal] = "<character-literal>",
	[t_hexadecimal_literal] = "<hexadecimal-literal>",
	
	// identifier:
	[t_identifier] = "<identifier>",
};

