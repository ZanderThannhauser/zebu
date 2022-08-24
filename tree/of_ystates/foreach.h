
struct yacc_state;
struct ystatetree;

void ystatetree_foreach(
	struct ystatetree* this,
	void (*runme)(struct yacc_state*));
