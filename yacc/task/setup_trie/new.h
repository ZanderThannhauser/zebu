
struct setup_trie_task* new_setup_trie_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* node,
	const char* name);
