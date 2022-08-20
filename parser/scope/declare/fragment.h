
struct scope;
struct regex;

void scope_declare_fragment(
	struct scope* this,
	char* name,
	struct regex* token);
