
	// absolute path:
	[ts_start]['<'] = ts_reading_abspath_literal,
		[ts_reading_abspath_literal][ANY] = ts_reading_abspath_literal,
		[ts_reading_abspath_literal]['>'] = ts_read_abspath_literal,
			[ts_read_abspath_literal][ANY] = ts_absolute_path,
	
