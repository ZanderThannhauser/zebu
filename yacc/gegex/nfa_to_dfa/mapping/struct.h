
struct gegex;
struct gegextree;

struct gegex_mapping
{
	struct gegextree* original_states; // must be the first
	struct gegex* combined_state;
	
	struct memory_arena* arena;
};
