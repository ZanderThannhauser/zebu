
struct unsignedset;

void unsignedset_foreach(
	const struct unsignedset* this,
	void (*runme)(unsigned));
