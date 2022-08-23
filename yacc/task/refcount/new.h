
struct memory_arena;

struct refcount_task* new_refcount_task(
	struct memory_arena* arena,
	struct gegex* start, struct gegex* node);
