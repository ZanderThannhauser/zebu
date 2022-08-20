
#include <stdbool.h>

struct regex;
struct regextree;

bool regextree_add(struct regextree* this, struct regex* ele);
