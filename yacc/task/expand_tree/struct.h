
#include "../struct.h"

struct expand_tree_task
{
	struct task super;
	
	struct yacc_stateinfo* stateinfo;
	struct lookahead_deps* ldeps;
	
	struct gegex* state;
	
	const char* reduce_as;
	struct tokenset* lookaheads;
};

