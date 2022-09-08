
struct stateinfo_node
{
	struct trie* trie;
	
	struct unsignedset* lookaheads; // owned
};

