
struct lookahead_deps_node
{
	struct gegex* a; // must be first
	struct gegexset* b;
	
	struct memory_arena* arena;
};
