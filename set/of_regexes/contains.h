
#include <stdbool.h>

struct regexset;

bool regexset_contains(
	struct regexset* this,
	const void* ptr);
