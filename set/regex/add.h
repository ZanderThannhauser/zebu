
#include <stdbool.h>

struct regexset;
struct regex;

bool regexset_add(
	struct regexset* this,
	struct regex* addme);
