
struct dfa_from_id_node
{
	unsigned id; // must be the first
	
	struct regex* token;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

