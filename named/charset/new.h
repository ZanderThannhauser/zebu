
#include <parser/charset/charset.h>

struct string;

struct named_charset* new_named_charset(
	struct string* name,
	charset_t charset);
