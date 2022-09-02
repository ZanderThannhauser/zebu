
struct named_charset
{
	struct string* name;
	bool is_complement;
	struct unsignedcharset* charset;
};

