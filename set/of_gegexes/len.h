
struct gegexset;

unsigned gegexset_len(const struct gegexset* this);

#define GEGEXSET_LENGTH(obj) \
	struct gegexset*: gegexset_len(obj), \
	const struct gegexset*: gegexset_len(obj)



