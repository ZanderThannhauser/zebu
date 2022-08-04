
struct memory_arena;

struct explore_lookaheads_task* new_explore_lookaheads_task(
	struct gegex* start,
	const char* name,
	struct gegex* node,
	const char* invocation,
	struct memory_arena* scratchpad);
