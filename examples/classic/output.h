extern const unsigned zebu_shifts[51][28];
extern const unsigned zebu_reduces[52][25];
extern const unsigned zebu_lexer[109][123];
extern const unsigned zebu_firsts[29][28];
extern const unsigned zebu_starts[52];
extern const unsigned zebu_defaults[53];
extern const unsigned zebu_EOFs[103];
extern const unsigned zebu_accepts[110];
extern const char* zebu_grammar_names[30];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
