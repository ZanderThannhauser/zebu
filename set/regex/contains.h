
#include <stdbool.h>

struct regexset;
struct regex;

bool regexset_contains(
	struct regexset* this,
	struct regex* element);
