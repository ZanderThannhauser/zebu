
#ifndef GEGEXSET_LENGTH
#define GEGEXSET_LENGTH(obj)
#endif

#ifndef HEAP_LENGTH
#define HEAP_LENGTH(obj)
#endif

#define len(obj) \
	_Generic((obj) \
		GEGEXSET_LENGTH(obj) \
		HEAP_LENGTH(obj))

