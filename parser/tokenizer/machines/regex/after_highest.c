
#include "../ANY.h"
#include "after_highest.h"

const enum tokenizer_state regex_after_highest_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	#include "../fragments/skip_comments.h"
	
	// highest:
		// open paren:
		#include "../fragments/oparen.h"
		
		// open sqaure:
		#include "../fragments/osquare.h"
		
		// identifier:
		#include "../fragments/identifier.h"
		
		// string literal:
		#include "../fragments/string_literal.h"
		
		// character literal:
		#include "../fragments/character_literal.h"
		
		// dot:
		#include "../fragments/dot.h"
		
	// suffixes:
		// question mark:
		#include "../fragments/qmark.h"
		
		// plus:
		#include "../fragments/plus.h"
		
		// asterisk:
		#include "../fragments/asterisk.h"
		
		// ocurly:
		#include "../fragments/ocurly.h"
	
	// and operator:
		#include "../fragments/ampersand.h"
	
	// xor operator:
		#include "../fragments/caret.h"
	
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




















