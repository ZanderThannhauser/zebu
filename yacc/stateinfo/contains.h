
#include <stdbool.h>

struct yacc_stateinfo;
struct gegex;

bool yacc_stateinfo_contains(
	struct yacc_stateinfo* this,
	struct gegex* state);
