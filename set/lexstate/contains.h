
#include <stdbool.h>

struct lexstateset;
struct lex_state;

bool lexstateset_contains(
	const struct lexstateset* this,
	struct lex_state* element);
