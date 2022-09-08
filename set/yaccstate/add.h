
#include <stdbool.h>

struct yaccstateset;
struct yacc_state;

bool yaccstateset_add(
	struct yaccstateset* this,
	struct yacc_state* ele);
