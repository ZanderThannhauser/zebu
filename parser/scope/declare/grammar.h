
struct scope;
struct gegex;

void scope_declare_grammar(
	struct scope* this,
	char* name,
	struct gegex* start,
	struct gegex* end);
