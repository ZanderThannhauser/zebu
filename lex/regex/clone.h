
struct memory_arena;
struct regex;

struct regex* regex_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* in);

struct clone_nfa_bundle {
	struct regex* start, *end;
} regex_clone_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* start,
	struct regex* end);

