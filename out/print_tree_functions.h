
#include <stdio.h>

struct avl_tree_t;

void print_tree_function_prototypes(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream);

void print_tree_functions(
	struct avl_tree_t* structinfos,
	const char* prefix,
	FILE* stream);
