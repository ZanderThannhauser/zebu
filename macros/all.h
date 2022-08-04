
#ifndef GEGEXSET_ALL
#define GEGEXSET_ALL(obj, runme) ,
#endif

#define all(obj, runme) \
	_Generic((obj), \
		GEGEXSET_ALL(obj, runme))

