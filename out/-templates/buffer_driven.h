
#include <stddef.h>

struct <PREFIX>_state;

struct <PREFIX>_state* new_<PREFIX>_state();

void <PREFIX>_reset(struct <PREFIX>_state* this);

void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length);

void <PREFIX>_parse_EOF(struct <PREFIX>_state* this);

void free_<PREFIX>_state(struct <PREFIX>_state* this);
