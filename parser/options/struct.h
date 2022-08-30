
struct regex;

struct options
{
	struct {
		struct dlink *head, *tail;
	} disambiguatations;
	
	struct regex *skip;
	struct regex *token_skip;
};

