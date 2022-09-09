
struct stateinfo;
struct trie;

struct unsignedset* stateinfo_get_lookaheads(
	struct stateinfo* this,
	struct trie* trie);
