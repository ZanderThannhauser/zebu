
struct memory_arena;
struct regex;

struct regex* regex_clone(
	struct regex* in,
	struct memory_arena* arena);
	
struct clone_nfa_bundle {
	struct regex* start, *end;
} regex_clone_nfa(
	struct memory_arena* arena,
	struct regex* start,
	struct regex* end);

