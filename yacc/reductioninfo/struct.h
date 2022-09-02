
struct reductioninfo
{
	unsigned index;
	
	char* tagname;
	
	enum {
		rik_token,
		rik_grammar,
		rik_subtrie,
	} kind;
	union {
		struct {
		} token;
		struct {
			const char* name;
		} grammar;
		struct {
		} subtrie;
	};
	
	unsigned refcount;
	
	struct reductioninfo* prev;
};

