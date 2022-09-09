
#include <stdio.h>

struct reductioninfo;
struct structinfo;

void reductioninfo_print_source(
	struct reductioninfo* this,
	struct structinfo* structinfo,
	FILE* stream);
