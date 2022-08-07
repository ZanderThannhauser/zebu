extern const unsigned zebu_shifts[29][23];
extern const unsigned zebu_reduces[30][20];
extern const unsigned zebu_popcounts[30][20];
extern const unsigned zebu_lexer[80][123];
extern const unsigned zebu_starts[30];
extern const unsigned zebu_defaults[46];
extern const unsigned zebu_EOFs[49];
extern const unsigned zebu_accepts[82];
extern const unsigned start_grammar_id;
extern const char* zebu_grammar_names[24];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
