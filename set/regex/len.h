
struct regexset;

unsigned regexset_len(const struct regexset* this);

#define REGEXSET_LENGTH(obj) \
	, struct regexset*: regexset_len(obj) \
	, const struct regexset*: regexset_len(obj)


