
struct regex;

struct options
{
	struct {
		struct dlink *head, *tail;
	} disambiguatations;
	
	struct regex *skip;
	struct regex *token_skip;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

