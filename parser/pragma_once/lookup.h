
#include <stdbool.h>

struct pragma_once;

int pragma_once_lookup(
	struct pragma_once* this,
	bool* out,
	int fd);
