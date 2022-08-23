
struct yacc_state;
struct lex;
struct memory_arena;

void lex_simplify_tokenizer(
	struct memory_arena* arena,
	struct lex* this,
	struct yacc_state* start);
