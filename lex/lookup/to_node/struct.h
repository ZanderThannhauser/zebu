
struct dfa_to_id_node
{
	struct regex* token; // must be the first
	
	unsigned id;
	
	struct memory_arena* arena;
};

