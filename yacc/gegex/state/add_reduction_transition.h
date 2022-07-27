
struct gegex;
struct memory_arena;

void gegex_add_reduction_transition(
	struct gegex* from,
	struct memory_arena* arena,
	unsigned token,
	char* reduce_to);
