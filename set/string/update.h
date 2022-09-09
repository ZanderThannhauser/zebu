
#include <stdbool.h>

struct stringset;

bool stringset_update(
	struct stringset* this,
	const struct stringset* other);
