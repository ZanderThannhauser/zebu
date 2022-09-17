
#include <stdio.h>

struct avl_tree_t;

void print_free_function_prototypes(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream);

void print_free_functions(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream);
