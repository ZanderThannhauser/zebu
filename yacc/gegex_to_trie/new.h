
struct gegex_to_trie* new_gegex_to_trie(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* gegex,
	const char* trie);
