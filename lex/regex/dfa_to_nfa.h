
#include <parser/token/rbundle.h>

struct memory_arena;

struct rbundle regex_dfa_to_nfa(struct regex* dfa, struct memory_arena* scratchpad);
