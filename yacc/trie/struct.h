
struct trie
{
	struct reductioninfo* reductioninfo;
	
	struct structinfo* structinfo;
	
	struct string* reduce_as; // name of trie
	
	struct string* grammar; // name of grammar rule
	
	struct {
		struct trie_transition {
			unsigned token;
			struct unsignedset* whitespace;
			struct trie* to;
		}** data;
		unsigned n, cap;
	} transitions;
	
	struct {
		struct trie_grammar_transition {
			struct string* grammar;
			struct trie* to;
		}** data;
		unsigned n, cap;
	} grammars;
};

