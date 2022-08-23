
struct named_token
{
	char* name;
	struct regex* token;
	
	struct memory_arena* arena;
};
