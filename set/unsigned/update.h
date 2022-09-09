
#include <stdbool.h>

struct unsignedset;

bool unsignedset_update(
	struct unsignedset* this,
	const struct unsignedset* other);
