
struct yacc_stateinfo_node
{
	struct gegex* state;
	
	const char* grammar;
	
	struct tokenset* lookaheads; // "owns" the lookaheads
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

