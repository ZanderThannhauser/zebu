
#include "../struct.h"

struct percolate_lookaheads_task
{
	struct task super;
	
	struct yacc_stateinfo* stateinfo;
	
	struct gegex* state;
	
	struct lookahead_deps* ldeps;
};

