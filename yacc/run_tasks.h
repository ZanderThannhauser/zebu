
struct memory_arena;

void run_tasks(
	struct yacc_shared* shared,
	struct memory_arena* scratchpad,
	unsigned EOF_token_id);
