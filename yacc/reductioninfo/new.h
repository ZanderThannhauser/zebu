
#include "kind.h"

struct reductioninfo* new_reductioninfo(
	enum reductioninfo_kind kind,
	struct structinfo* structinfo,
	struct string* grammar,
	struct reductioninfo* prev);
