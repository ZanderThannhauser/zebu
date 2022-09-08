
#include "../ANY.h"
#include "after_suffix.h"

const enum tokenizer_state regex_after_suffix_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	// highest:
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
		
	// prefixes:
		// exclamation mark:
		#include "../fragments/emark.h"
	
	// and operator:
		#include "../fragments/ampersand.h"
	
	// or operator:
		#include "../fragments/vertical_bar.h"
	
	// end of expression:
		// close paren:
		#include "../fragments/cparen.h"
		
		// semicolon
		#include "../fragments/semicolon.h"
		
		// colon
		#include "../fragments/colon.h"
		
		// gravemark
		#include "../fragments/gravemark.h"
};




















