
#include <stdio.h>

struct reductioninfo;
struct structinfo;

void reductioninfo_print_source(
	struct reductioninfo* this,
	struct structinfo* structinfo,
	const char* grammar,
	const char* prefix,
	FILE* stream);
