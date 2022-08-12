
#include "../struct.h"

struct add_transition_task
{
	struct task super;
	
	struct yacc_state** write_to_me;
	
	struct yacc_stateinfo* stateinfo;
};

