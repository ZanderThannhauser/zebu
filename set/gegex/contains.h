
#include <stdbool.h>

struct gegexset;
struct gegex;

bool gegexset_contains(
	const struct gegexset* this,
	struct gegex* element);
