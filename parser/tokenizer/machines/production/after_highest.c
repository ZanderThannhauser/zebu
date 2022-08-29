
#include "../ANY.h"

#include "after_highest.h"

const enum tokenizer_state production_after_highest_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	#include "../fragments/skip_comments.h"
	
	// highest:
		// hashtag:
		#include "../fragments/hashtag.h"
		
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
	
	// suffixes:
		// plus:
		#include "../fragments/plus.h"
		// asterisk
		#include "../fragments/asterisk.h"
		// qmark
		#include "../fragments/qmark.h"
	
	// subroot:
		// percent:
		#include "../fragments/percent.h"
	
	// or:
		// vertical bar:
		#include "../fragments/vertical_bar.h"
	
	// end of expression:
		// close paren:
		#include "../fragments/cparen.h"
		
		// colon:
		#include "../fragments/colon.h"
		
		// semicolon
		#include "../fragments/semicolon.h"
		
};




















