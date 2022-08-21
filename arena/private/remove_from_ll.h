
struct memory_arena;
struct memory_arena_header;

void remove_from_ll(
	struct memory_arena* this,
	struct memory_arena_header* block);
