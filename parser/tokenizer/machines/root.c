
#include "ANY.h"
#include "root.h"

enum tokenizer_state root_machine[number_of_tokenizer_states][256] = {
	
	#include "fragments/skip_whitespace.h"
	
	#include "fragments/skip_comments.h"
	
	#include "fragments/directive.h"
	
	#include "fragments/bracketed_identifier.h"
	
	#include "fragments/gravemarked_identifier.h"
	
	#include "fragments/parenthesised_identifier.h"
	
	#include "fragments/identifier.h"
	
	#include "fragments/EOF.h"
};

