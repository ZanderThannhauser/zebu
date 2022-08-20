
#include <stdbool.h>

struct regex;
struct regexset;

bool regexset_add(struct regexset* this, struct regex* ptr);
