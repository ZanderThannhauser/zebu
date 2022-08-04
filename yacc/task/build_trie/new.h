
struct build_trie_task* new_build_trie_task(
	struct memory_arena* scratchpad,
	const char* name,
	struct gegex* start,
	struct gegex* mirrorme,
	struct gegex* building,
	unsigned pop_count);
