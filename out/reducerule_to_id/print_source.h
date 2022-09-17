
#include <stdio.h>

struct reducerule_to_id;
struct string_to_id;

void reducerule_to_id_print_source(
	struct reducerule_to_id* this,
	struct string_to_id* stoi,
	const char* prefix,
	FILE* stream);
