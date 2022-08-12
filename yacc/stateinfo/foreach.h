
void yacc_stateinfo_foreach(
	struct yacc_stateinfo* this,
	void (*runme)(struct gegex* state, const char* grammar, struct tokenset*));
