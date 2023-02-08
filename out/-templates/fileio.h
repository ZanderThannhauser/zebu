
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>

{{PARSE_TREE_STRUCTS}}

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

struct zebu_$start* {{PREFIX}}_parse(FILE* stream);
