
#ifndef GEGEXSET_LENGTH
#define GEGEXSET_LENGTH(obj) ,
#endif

#define len(obj) \
	_Generic((obj), \
		GEGEXSET_LENGTH(obj))

