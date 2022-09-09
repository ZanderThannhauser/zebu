
struct string;
struct trie;

struct named_trie* new_named_trie(
	struct string* name,
	struct trie* trie);
