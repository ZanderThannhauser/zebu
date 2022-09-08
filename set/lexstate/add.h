
#include <stdbool.h>

struct lexstateset;
struct lex_state;

bool lexstateset_add(
	struct lexstateset* this,
	struct lex_state* ele);
