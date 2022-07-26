
struct regex;
struct regexset;

struct mapping
{
	struct regexset* original_states; // must be the first
	struct regex* combined_state;
};
