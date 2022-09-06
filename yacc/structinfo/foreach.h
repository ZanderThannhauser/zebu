
#include "node_kind.h"

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(
		struct string* name,
		enum structinfo_node_kind kind,
		struct string* grammar));
