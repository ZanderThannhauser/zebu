extern const unsigned zebu_shifts[93][40];
extern const unsigned zebu_reduces[95][29];
extern const unsigned zebu_popcounts[95][29];
extern const unsigned zebu_lexer[111][123];
extern const unsigned zebu_starts[95];
extern const unsigned zebu_defaults[56];
extern const unsigned zebu_EOFs[105];
extern const unsigned zebu_accepts[112];
extern const unsigned start_grammar_id;
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
