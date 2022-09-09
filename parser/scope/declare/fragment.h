
struct scope;
struct string;
struct regex;

void scope_declare_fragment(
	struct scope* this,
	struct string* name,
	struct regex* token);
