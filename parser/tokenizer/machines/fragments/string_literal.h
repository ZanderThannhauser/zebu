
[ts_start]['\"'] = ts_reading_string_literal,
	[ts_reading_string_literal][ANY] = ts_reading_string_literal,
	[ts_reading_string_literal]['\\'] = ts_reading_string_escape,
		[ts_reading_string_escape][ANY] = ts_reading_string_literal,
	[ts_reading_string_literal]['\"'] = ts_read_string_literal,
		[ts_read_string_literal][ANY] = ts_string_literal,
		
