
#include "../struct.h"

struct build_ystate_task
{
	struct task super;
	
	struct yacc_state* state;
	
	struct yacc_stateinfo* stateinfo;
};

