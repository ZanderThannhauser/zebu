
#ifndef TYPEDEF_CHARSET
#define TYPEDEF_CHARSET

#include <stdint.h>

typedef uint16_t charset_t __attribute__ ((vector_size (256)));

#endif
