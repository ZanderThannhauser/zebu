
struct regex;

struct options
{
	char* start;
	
	struct regex *skip;
	
	struct {
		struct dlink *head, *tail;
	} disambiguatations;
};

