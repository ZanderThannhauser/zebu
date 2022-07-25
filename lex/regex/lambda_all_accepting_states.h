
#include <stdbool.h>

struct regex;
struct memory_arena;

void regex_lambda_all_accepting_states(
	struct regex* regex,
	struct memory_arena* arena,
	struct regex* dest,
	bool new_accepting);
