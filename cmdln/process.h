
struct cmdln* cmdln_process(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	int argc, char* const* argv);
