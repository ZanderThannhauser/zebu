
struct regexset;
struct regex;

void regexset_foreach(
	struct regexset* this,
	void (*runme)(struct regex* state));
