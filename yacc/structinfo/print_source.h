
#include <stdio.h>

struct structinfo;
struct stringset;

void structinfo_print_source(
	struct structinfo* this,
	struct string* name,
	const char* prefix,
	FILE* stream);
