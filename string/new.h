
struct tokenizer;

struct string* new_string_without_copy(char* str);

struct string* new_string(const char* str);

struct string* new_string_from_tokenchars(struct tokenizer* tokenizer);

struct string* new_string_from_format(const char* fmt, ...);


