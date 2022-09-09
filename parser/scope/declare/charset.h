
#include <parser/charset/charset.h>

struct scope;
struct string;

void scope_declare_charset(
	struct scope* this,
	struct string* name,
	charset_t charset);
