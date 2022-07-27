
struct memory_arena;
struct gegex;

struct lambda_subgrammars_task* new_lambda_subgrammars_task(
	const char* name,
	struct gegex* node,
	struct memory_arena* scratchpad);
