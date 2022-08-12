
#include "../struct.h"

struct setup_start_task
{
	struct task super;
	
	struct yacc_tree* tree;
	
	struct lookahead_deps* ldeps;
	
	struct gegex* state;
	
	struct tokenset* lookaheads;
};

