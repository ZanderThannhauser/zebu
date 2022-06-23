
struct scope;
struct regex;

void scope_declare_token(
	struct scope* this,
	char* name,
	struct regex* token);
