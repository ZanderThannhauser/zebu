
#include <stdbool.h>

struct memory_arena;

struct charset* new_charset(
	struct memory_arena* arena,
	const unsigned char* src, size_t len,
	bool is_complement);
