
#include <stdio.h>

struct yacc_stateinfo;
struct avl_tree_t;

void yacc_stateinfo_dotout(
	struct yacc_stateinfo* this,
	struct avl_tree_t* new_grammar,
	FILE* stream);
