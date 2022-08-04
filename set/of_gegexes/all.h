
bool gegexset_all(
	const struct gegexset* this,
	bool (*runme)(struct gegex* state));
	struct gegexset;

#define GEGEXSET_ALL(obj, runme) \
	struct gegexset*: gegexset_all(obj, runme), \
	const struct gegexset*: gegexset_all(obj, runme)


