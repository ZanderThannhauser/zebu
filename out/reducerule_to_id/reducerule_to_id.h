
struct reducerule_to_id;
struct string;
struct reductioninfo;
struct structinfo;

unsigned reducerule_to_id(
	struct reducerule_to_id* this,
	struct string* reduce_as,
	struct string* grammar,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo);
