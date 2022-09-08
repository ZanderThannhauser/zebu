
[ts_start]['#'] = ts_reading_hashtag,
	[ts_reading_hashtag]['a' ... 'z'] = ts_reading_hashtag2,
	[ts_reading_hashtag]['A' ... 'Z'] = ts_reading_hashtag2,
		[ts_reading_hashtag2][ANY] = ts_hashtag_scalar,
		[ts_reading_hashtag2]['_'] = ts_reading_hashtag2,
		[ts_reading_hashtag2]['1' ... '9'] = ts_reading_hashtag2,
		[ts_reading_hashtag2]['a' ... 'z'] = ts_reading_hashtag2,
		[ts_reading_hashtag2]['A' ... 'Z'] = ts_reading_hashtag2,
		[ts_reading_hashtag2]['['] = ts_reading_hashtag3,
			[ts_reading_hashtag3][']'] = ts_reading_hashtag4,
				[ts_reading_hashtag4][ANY] = ts_hashtag_array,

