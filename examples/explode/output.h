extern const unsigned zebu_shifts[21][23];
extern const unsigned zebu_reduces[22][19];
extern const unsigned zebu_lexer[260][98];
extern const unsigned zebu_firsts[24][20];
extern const unsigned zebu_starts[22];
extern const unsigned zebu_defaults[1];
extern const unsigned zebu_EOFs[215];
extern const unsigned zebu_accepts[261];
extern const char* zebu_grammar_names[25];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
