
struct tokenset;

void tokenset_foreach(
	struct tokenset* this,
	void (*runme)(unsigned token));
