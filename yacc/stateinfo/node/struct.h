
struct stateinfo_node
{
	struct trie* trie;
	
	struct unsignedset* whitespace;
	struct unsignedset* lookaheads;
};

