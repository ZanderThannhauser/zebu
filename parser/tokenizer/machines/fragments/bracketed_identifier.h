
[ts_start]['['] = ts_reading_bracketed_identifier,
	[ts_reading_bracketed_identifier][ANY] = ts_reading_bracketed_identifier,
	[ts_reading_bracketed_identifier][']'] = ts_read_bracketed_identifier,
		[ts_read_bracketed_identifier][ANY] = ts_bracketed_identifier,
