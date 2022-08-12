
#ifndef ENUM_TASK_KIND
#define ENUM_TASK_KIND

enum task_kind
{
	tk_refcount,
	
	tk_setup_trie,
	tk_build_trie,
	
	tk_explore_firsts,
	tk_percolate_firsts,
	
	tk_setup_start,
	
	tk_expand_tree,
	
	tk_percolate_lookaheads,
	
	tk_free_lookahead_deps,
	
	tk_add_transition,
	
	tk_build_ystate,
};

#endif
