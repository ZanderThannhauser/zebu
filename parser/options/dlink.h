
#if 0
struct dlink
{
	struct dop {
		enum dop_kind {
			dk_literal,
			dk_regex,
			dk_string,
		} kind;
		
		union {
			struct {
				unsigned char* chars;
				unsigned len;
			} s;
		};
	} left, right;
	
	int cmp;
	
	struct dlink* next;
};
#endif
