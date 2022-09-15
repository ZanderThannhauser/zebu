
struct stateinfo;
struct trie;
struct unsignedset;

struct stateinfo_node* stateinfo_add(
	struct stateinfo* this,
	struct trie* trie,
	struct unsignedset* whitespace,
	struct unsignedset* lookaheads);
