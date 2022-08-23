
void read_inline_grammar(
	#ifdef WITH_ARENAS
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
