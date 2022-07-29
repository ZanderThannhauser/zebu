extern const unsigned zebu_shifts[14][14];
extern const unsigned zebu_reduces[16][10];
extern const unsigned zebu_lexer[22][58];
extern const unsigned zebu_firsts[15][14];
extern const unsigned zebu_starts[16];
extern const unsigned zebu_defaults[1];
extern const unsigned zebu_EOFs[22];
extern const unsigned zebu_accepts[23];
extern const char* zebu_grammar_names[16];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
