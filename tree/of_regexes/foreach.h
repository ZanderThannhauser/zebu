
struct regex;
struct regextree;

void regextree_foreach(
	struct regextree* this,
	void (*runme)(struct regex*));
