
struct format_flags
{
	int max_field_width;
	enum length_modifier {
		lm_char,
		lm_short,
		lm_int,
		lm_long,
		lm_long_long,
		lm_long_double,
		lm_intmax,
		lm_size,
		lm_ptrdiff,
	} length_modifier;
	const char* length_modifier_text;
	char conversion; // 'i', 'd', 'u', 'o', 'x', 'X', 'f', 'g' ...
	
	const char* ctype; // "char", "int", "wchar_t", ...
	
	unsigned refcount;
};

