
#ifndef ENUM_TASK_KIND
#define ENUM_TASK_KIND

enum task_kind
{
	tk_refcount,
	
	tk_setup_trie,
	
	tk_build_trie,
	
	tk_explore_firsts,
	
	tk_percolate_firsts,
	
	tk_explore_lookaheads,
	
	tk_percolate_lookaheads,
	
	tk_add_reductions,
	
	tk_lambda_subgrammars,
};

#endif
