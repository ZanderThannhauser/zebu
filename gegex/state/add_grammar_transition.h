
struct gegex;
struct string;
struct structinfo;

void gegex_add_grammar_transition(
	struct gegex* from,
	struct string* grammar_name,
	struct structinfo* structinfo,
	struct gegex* to);
