
struct dfa_to_id_node* new_dfa_to_id_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	unsigned id, struct regex* token);
