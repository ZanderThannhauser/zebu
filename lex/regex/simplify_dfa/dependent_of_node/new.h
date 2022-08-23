
struct dependent_of_node* new_dependent_of_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b);
