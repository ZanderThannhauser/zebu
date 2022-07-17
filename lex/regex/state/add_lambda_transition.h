
struct regex;
struct memory_arena;

void regex_add_lambda_transition(
	struct regex* from,
	struct memory_arena* arena,
	struct regex* to);
