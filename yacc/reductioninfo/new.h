
#include "kind.h"

struct reductioninfo* new_reductioninfo(
	enum reductioninfo_kind kind,
	struct stringset* tags,
	struct string* grammar,
	struct reductioninfo* prev);
