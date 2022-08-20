
// numeric_literal:
[ts_start]['0' ... '9'] = ts_reading_numeric_literal,
	[ts_reading_numeric_literal][ANY] = ts_numeric_literal,
	[ts_reading_numeric_literal]['0' ... '9'] = ts_reading_numeric_literal,

