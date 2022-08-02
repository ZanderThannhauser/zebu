
struct gegex;
struct gegexset;

struct gegex_mapping
{
	struct gegexset* original_states; // must be the first
	struct gegex* combined_state;
};
