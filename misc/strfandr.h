
struct memory_arena;

char* strfandr(
	struct memory_arena* arena,
	const char* original,
	const char* findme,
	const char* replacewith);
