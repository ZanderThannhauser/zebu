
#include "../ANY.h"

#include "inside_or.h"

const enum tokenizer_state production_inside_subdefinitions_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	#include "../fragments/skip_comments.h"
	
	// highest:
		// charset expression:
		#include "../fragments/osquare.h"
		
		// token expression:
		#include "../fragments/gravemark.h"
		
		// open paren:
		#include "../fragments/oparen.h"
		
		// grammar name:
		#include "../fragments/identifier.h"
		
		// string literal:
		#include "../fragments/string_literal.h"
		
		// character literal:
		#include "../fragments/character_literal.h"
		
	// subroot:
		// percent:
		#include "../fragments/percent.h"
	
	// end of expression:
		// close paren:
		#include "../fragments/cparen.h"
		
		// colon:
		#include "../fragments/colon.h"
		
		// semicolon
		#include "../fragments/semicolon.h"
};




















