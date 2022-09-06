
struct reductioninfo
{
	struct stringset* tags; // could be null
	
	enum {
		rik_token,
		rik_grammar,
		rik_trie,
	} kind;
	
	struct string* grammar;
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

