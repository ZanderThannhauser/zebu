
struct memory_arena;
struct regex;

struct regex* regex_nfa_to_dfa(struct regex* in, struct memory_arena* arena);
