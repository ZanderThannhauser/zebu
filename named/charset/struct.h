
struct charset;

struct named_charset
{
	char* name;
	
	struct charset* charset;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

