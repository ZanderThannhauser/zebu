
struct quack;

unsigned quack_len(const struct quack* this);

#define QUACK_LENGTH(obj) \
	, struct quack*: quack_len(obj) \
	, const struct quack*: quack_len(obj)


