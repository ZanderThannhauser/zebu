
#include "machines/state.h"

#include "../token.h"

struct tokenizer;

enum token read_token(
	struct tokenizer* this,
	enum tokenizer_state machine[number_of_tokenizer_states][256]);
