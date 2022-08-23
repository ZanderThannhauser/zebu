
struct gegex;

void gegextree_enumerate(
	const struct gegextree* this,
	void (*runme)(unsigned, struct gegex*));
