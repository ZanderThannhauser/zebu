extern const unsigned zebu_shifts[106][63];
extern const unsigned zebu_reduces[107][38];
extern const unsigned zebu_popcounts[107][38];
extern const unsigned zebu_lexer[270][127];
extern const unsigned zebu_starts[107];
extern const unsigned zebu_defaults[91];
extern const unsigned zebu_EOFs[270];
extern const unsigned zebu_accepts[271];
extern const unsigned start_grammar_id;
extern const char* zebu_grammar_names[65];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
