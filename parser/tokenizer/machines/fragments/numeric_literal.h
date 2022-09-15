
// decimal_literal or hexadecimal_literal:
[ts_start]['0'] = ts_reading_numeric_literal,
	[ts_reading_numeric_literal][ANY] = ts_decimal_literal,
	[ts_reading_numeric_literal]['x'] = ts_reading_hexadecimal_literal,
		[ts_reading_hexadecimal_literal]['0' ... '9'] = ts_reading_hexadecimal_literal2,
		[ts_reading_hexadecimal_literal]['a' ... 'f'] = ts_reading_hexadecimal_literal2,
		[ts_reading_hexadecimal_literal]['A' ... 'F'] = ts_reading_hexadecimal_literal2,
			[ts_reading_hexadecimal_literal2][    ANY    ] = ts_hexadecimal_literal,
			[ts_reading_hexadecimal_literal2]['0' ... '9'] = ts_reading_hexadecimal_literal2,
			[ts_reading_hexadecimal_literal2]['a' ... 'f'] = ts_reading_hexadecimal_literal2,
			[ts_reading_hexadecimal_literal2]['A' ... 'F'] = ts_reading_hexadecimal_literal2,
	[ts_reading_numeric_literal]['0' ... '7'] = ts_reading_octal_literal,
		[ts_reading_octal_literal][ANY] = ts_octal_literal,
		[ts_reading_octal_literal]['0' ... '7'] = ts_reading_octal_literal,
[ts_start]['1' ... '9'] = ts_reading_decimal_literal,
	[ts_reading_decimal_literal][ANY] = ts_decimal_literal,
	[ts_reading_decimal_literal]['0' ... '9'] = ts_reading_decimal_literal,

