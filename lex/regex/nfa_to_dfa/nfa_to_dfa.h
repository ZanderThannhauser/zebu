struct regex* regex_nfa_to_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* in
);
