
struct regex;
struct stateset;

struct mapping
{
	struct stateset* original_states; // must be the first
	struct regex* combined_state;
};
