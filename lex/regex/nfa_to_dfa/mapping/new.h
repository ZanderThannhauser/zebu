
struct regexset;
struct regex;

struct regex_mapping* new_regex_mapping(
	struct memory_arena* arena,
	struct regexset* set, struct regex* state);
