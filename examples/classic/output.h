extern const unsigned zebu_shifts[51][27];
extern const unsigned zebu_reduces[52][24];
extern const unsigned zebu_lexer[95][123];
extern const unsigned zebu_firsts[28][27];
extern const unsigned zebu_starts[52];
extern const unsigned zebu_defaults[48];
extern const unsigned zebu_accepts[96];
extern const char* zebu_grammar_names[29];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
