
struct regex;
struct regexset;

struct regex_mapping
{
	struct regexset* original_states; // must be the first
	struct regex* combined_state;
	
	struct memory_arena* arena;
};
