
struct named_token
{
	char* name;
	struct regex* token;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};
