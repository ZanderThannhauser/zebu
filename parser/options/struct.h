
struct regex;

struct options
{
	#if 0
	struct {
		struct dlink *head, *tail;
	} disambiguatations;
	#endif
	
	struct regex *skip;
	struct regex *token_skip;
};

