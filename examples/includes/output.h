extern const unsigned zebu_shifts[11][11];
extern const unsigned zebu_reduces[12][6];
extern const unsigned zebu_lexer[12][101];
extern const unsigned zebu_firsts[11][11];
extern const unsigned zebu_starts[12];
extern const unsigned zebu_defaults[1];
extern const unsigned zebu_EOFs[10];
extern const unsigned zebu_accepts[13];
extern const char* zebu_grammar_names[12];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
