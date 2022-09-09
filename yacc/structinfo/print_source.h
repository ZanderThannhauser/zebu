
#include <stdio.h>

struct structinfo;
struct stringset;

void structinfo_print_source(
	struct structinfo* this,
	struct stringset* done,
	FILE* stream);
