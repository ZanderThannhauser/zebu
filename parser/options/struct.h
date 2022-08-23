
struct regex;

struct options
{
	struct regex *skip;
	
	struct regex *token_skip;
	
	struct {
		struct dlink *head, *tail;
	} disambiguatations;
};

