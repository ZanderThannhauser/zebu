
struct build_tokenizer_node* new_build_tokenizer_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenset* token_ids,  // needs to be cloned
	struct tokensetset* matches,
	struct lex_state* start);
