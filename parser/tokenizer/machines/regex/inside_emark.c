
#include "../ANY.h"

#include "root.h"

const enum tokenizer_state regex_inside_emark_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	// highest:
		// open sqaure:
		#include "../fragments/osquare.h"
		
		// open paren:
		#include "../fragments/oparen.h"
		
		// identifier:
		#include "../fragments/identifier.h"
		
		// string literal:
		#include "../fragments/string_literal.h"
		
		// character literal:
		#include "../fragments/character_literal.h"
		
		// dot:
		#include "../fragments/dot.h"
	
	// difference:
		// exclamation mark:
		#include "../fragments/emark.h"
	
};




















