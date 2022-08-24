
struct lex_state;
struct lstatetree;

void lstatetree_foreach(
	struct lstatetree* this,
	void (*runme)(struct lex_state*));
