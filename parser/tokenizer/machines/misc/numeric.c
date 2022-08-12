
#include "../ANY.h"

#include "numeric.h"

enum tokenizer_state numeric_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// numeric:
	[ts_start]['0' ... '9'] = ts_reading_numeric,
		[ts_reading_numeric][ANY] = ts_numeric,
		[ts_reading_numeric]['0' ... '9'] = ts_reading_numeric,
	
};

