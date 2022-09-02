
struct trie
{
	struct {
		struct reductioninfo* info;
		unsigned popcount;
		const char* as;
	} reduce;
};

#if 0
struct yacc_trie
{
	
	struct {
		struct transition {
			unsigned token;
			struct gegex* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct gtransition {
			char* grammar; // owned
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct rtransition {
			unsigned token;
			char* reduce_as; // owned
			unsigned popcount;
		}** data;
		size_t n, cap;
	} reduction_transitions;
	
	unsigned phase, refcount;
};

#endif
