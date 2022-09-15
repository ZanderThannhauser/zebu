
#include "../ANY.h"

#include "after_highest.h"

const enum tokenizer_state charset_after_highest_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
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
		// tilda:
		#include "../fragments/tilda.h"
	
	// range:
		// hypen:
		#include "../fragments/hypen.h"
	
	// intersect:
		// ampersand:
		#include "../fragments/ampersand.h"
	
	// symmetric difference:
		// caret:
		#include "../fragments/caret.h"
	
	// union:
		// vertical bar:
		#include "../fragments/vertical_bar.h"
		
		// comma:
		#include "../fragments/comma.h"
	
	// end of expression:
	
		// semicolon:
		#include "../fragments/semicolon.h"
		
		// close paren:
		#include "../fragments/cparen.h"
		
		// close square:
		#include "../fragments/csquare.h"
	
};




















