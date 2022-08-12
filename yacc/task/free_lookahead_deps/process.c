
#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/safe_insert.h>*/

/*#include <yacc/gegex/state/struct.h>*/

/*#include <named/grammar/struct.h>*/

/*#include <set/of_tokens/free.h>*/

/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/add.h>*/
/*#include <set/of_tokens/update.h>*/
/*#include <set/of_tokens/clone.h>*/

/*#include <heap/push.h>*/

/*#include "../../tree/new.h"*/
/*#include "../../tree/contains.h"*/
/*#include "../../tree/add.h"*/

/*#include "../expand_tree/new.h"*/

#include "../../lookahead_deps/free.h"
/*#include "../../lookahead_deps/add.h"*/

/*#include "../../shared/struct.h"*/
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
/*#include "new.h"*/
#include "process.h"

void free_lookahead_deps_task_process(struct task* super, struct yacc_shared* shared)
{
	struct free_lookahead_deps_task* const this = (void*) super;
	ENTER;
	
	free_lookahead_deps(this->ldeps);
	
	EXIT;
}
















