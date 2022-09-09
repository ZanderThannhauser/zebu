
struct unsignedsetset;
struct unsignedset;

void unsignedsetset_foreach(
	struct unsignedsetset* this,
	void (*runme)(struct unsignedset*));
