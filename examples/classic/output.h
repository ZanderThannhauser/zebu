extern const unsigned zebu_shifts[108][47];
extern const unsigned zebu_reduces[110][33];
extern const unsigned zebu_popcounts[110][33];
extern const unsigned zebu_lexer[108][123];
extern const unsigned zebu_starts[110];
extern const unsigned zebu_defaults[56];
extern const unsigned zebu_EOFs[108];
extern const unsigned zebu_accepts[109];
extern const char* zebu_grammar_names[49];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
