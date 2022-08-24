
struct regex;
struct regexset;

void regexset_foreach(
	const struct regexset* this,
	void (*runme)(struct regex* state));
