
struct charset;

struct named_charset
{
	char* name;
	
	struct charset* charset;
	
	struct memory_arena* arena;
};

