
#if 0
#include "../ANY.h"

#include "comparision.h"

enum tokenizer_state comparision_machine[number_of_tokenizer_states][256] = {
	
	#include "../fragments/skip_whitespace.h"
	
	// skip comments:
	[ts_start]['/'] = ts_after_slash,
		[ts_after_slash]['/'] = ts_skipping_comment,
			[ts_skipping_comment][ANY] = ts_skipping_comment,
			[ts_skipping_comment]['\n'] = ts_start,

	// comparision:
	[ts_start]['<'] = ts_after_lthan,
		[ts_after_lthan][ANY] = ts_lthan,
		
	[ts_start]['='] = ts_after_equal_to,
		[ts_after_equal_to][ANY] = ts_equal_to,
		
	[ts_start]['>'] = ts_after_gthan,
		[ts_after_gthan][ANY] = ts_gthan,
	
};




















#endif
