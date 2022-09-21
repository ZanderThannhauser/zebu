
#include "rbundle.h"

struct memory_arena;
struct regex;

struct regex* regex_clone(
	struct regex* in);

struct rbundle regex_clone_nfa(
	struct regex* start,
	struct regex* end);

