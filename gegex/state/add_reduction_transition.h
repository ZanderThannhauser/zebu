
struct gegex;
struct memory_arena;

void gegex_add_reduction_transition(
	struct gegex* from,
	unsigned token,
	char* reduce_as,
	unsigned popcount);
