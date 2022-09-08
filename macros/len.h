
#ifndef GEGEXSET_LENGTH
#define GEGEXSET_LENGTH(obj)
#endif

#ifndef GEGEXTREE_LENGTH
#define GEGEXTREE_LENGTH(obj)
#endif

#ifndef HEAP_LENGTH
#define HEAP_LENGTH(obj)
#endif

#ifndef REGEXSET_LENGTH
#define REGEXSET_LENGTH(obj)
#endif

#ifndef QUACK_LENGTH
#define QUACK_LENGTH(obj)
#endif

#define len(obj) \
	_Generic((obj) \
		GEGEXSET_LENGTH(obj) \
		GEGEXTREE_LENGTH(obj) \
		REGEXSET_LENGTH(obj) \
		QUACK_LENGTH(obj) \
		HEAP_LENGTH(obj))


