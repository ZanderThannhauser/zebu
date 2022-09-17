
#include <stdio.h>

struct structinfo;
struct stringset;

void structinfo_print_source(
	struct structinfo* this,
	const char* prefix,
	FILE* stream);
