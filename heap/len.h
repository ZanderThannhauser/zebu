
struct heap;

unsigned heap_len(const struct heap* this);

#define HEAP_LENGTH(obj) \
	, struct heap*: heap_len(obj) \
	, const struct heap*: heap_len(obj)



