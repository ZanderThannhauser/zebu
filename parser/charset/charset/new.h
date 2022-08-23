
#include <stdbool.h>

struct memory_arena;

struct charset* new_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const unsigned char* src, size_t len,
	bool is_complement);
