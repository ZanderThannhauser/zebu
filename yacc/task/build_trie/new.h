
struct build_trie_task* new_build_trie_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name,
	struct gegex* start,
	struct gegex* mirrorme,
	struct gegex* building,
	unsigned popcount);
