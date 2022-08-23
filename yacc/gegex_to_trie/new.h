
struct memory_arena;

struct gegex_to_trie* new_gegex_to_trie(
	struct memory_arena* arena,
	struct gegex* gegex,
	const char* trie);
