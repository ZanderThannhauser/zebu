
struct stringset;
struct string;

void stringset_foreach(
	const struct stringset* this,
	void (*runme)(struct string* element));
