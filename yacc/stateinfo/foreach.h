
struct stateinfo_node;

void stateinfo_foreach(
	struct stateinfo* this,
	void (*runme)(struct trie* trie, struct unsignedset* lookahead));

void stateinfo_foreach2(
	struct stateinfo* this,
	void (*runme)(struct stateinfo_node* ele));
