
struct gegex;
struct gegextree;

void gegextree_foreach(
	struct gegextree* this,
	void (*runme)(struct gegex*));
