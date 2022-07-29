extern const unsigned zebu_shifts[97][54];
extern const unsigned zebu_reduces[98][37];
extern const unsigned zebu_lexer[258][127];
extern const unsigned zebu_firsts[55][54];
extern const unsigned zebu_starts[98];
extern const unsigned zebu_defaults[58];
extern const unsigned zebu_EOFs[258];
extern const unsigned zebu_accepts[259];
extern const char* zebu_grammar_names[56];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
