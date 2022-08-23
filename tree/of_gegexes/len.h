
struct gegextree;

unsigned gegextree_len(const struct gegextree* this);

#define GEGEXTREE_LENGTH(obj) \
	, struct gegextree*: gegextree_len(obj) \
	, const struct gegextree*: gegextree_len(obj)



