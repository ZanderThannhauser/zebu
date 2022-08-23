
struct lex_state;

struct memory_arena;

void lex_state_add_transition(
	struct lex_state* this,
	unsigned char value,
	struct lex_state* to);
