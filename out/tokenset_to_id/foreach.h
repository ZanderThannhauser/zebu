
struct tokenset;

void tokenset_to_id_foreach(
	struct tokenset_to_id* this,
	void (*per_tokenset)(const struct tokenset*, unsigned id));
