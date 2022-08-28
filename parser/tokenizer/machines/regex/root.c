
#include "../ANY.h"

#include "root.h"

const enum tokenizer_state regex_root_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	// highest:
		#include "../fragments/osquare.h"
		
		#include "../fragments/oparen.h"
		
		#include "../fragments/identifier.h"
		
		#include "../fragments/string_literal.h"
		
		#include "../fragments/character_literal.h"
		
		#include "../fragments/dot.h"
	
	// prefixes:
		// exclamation mark:
		#include "../fragments/emark.h"
};




















