
struct gegex;
struct gegexset;

void gegexset_foreach(
	const struct gegexset* this,
	void (*runme)(struct gegex* state));
