
struct gegex;

void gegexset_foreach(
	const struct gegexset* this,
	void (*runme)(struct gegex* state));
