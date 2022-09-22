
#include "node_type.h"

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(
		struct string* name,
		enum structinfo_node_type type,
		struct string* grammar));
