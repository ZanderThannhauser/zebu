
struct lexstateset;
struct lex_state;

void lexstateset_foreach(
	struct lexstateset* this,
	void (*runme)(struct lex_state*));