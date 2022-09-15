
#include "../ANY.h"

#include "root.h"

const enum tokenizer_state charset_inside_intersect_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	#include "../fragments/skip_comments.h"
	
	// highest:
		// character literal:
		#include "../fragments/character_literal.h"
		
		// numeric literal:
		#include "../fragments/numeric_literal.h"
		
		// identifier:
		#include "../fragments/identifier.h"
		
		// open paren:
		#include "../fragments/oparen.h"
		
	// prefixes:
		// set not:
		#include "../fragments/emark.h"
	
};




















