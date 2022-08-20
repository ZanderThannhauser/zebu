
#include <stdbool.h>

struct regextree;
struct regex;

bool regextree_contains(struct regextree* this, struct regex* ele);
