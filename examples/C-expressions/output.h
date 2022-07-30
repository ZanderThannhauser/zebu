extern const unsigned zebu_shifts[99][56];
extern const unsigned zebu_reduces[100][38];
extern const unsigned zebu_lexer[270][127];
extern const unsigned zebu_firsts[57][56];
extern const unsigned zebu_starts[100];
extern const unsigned zebu_defaults[64];
extern const unsigned zebu_EOFs[270];
extern const unsigned zebu_accepts[271];
extern const char* zebu_grammar_names[58];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
