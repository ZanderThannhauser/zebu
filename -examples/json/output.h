extern const unsigned zebu_shifts[19][14];
extern const unsigned zebu_reduces[21][12];
extern const unsigned zebu_lexer[35][126];
extern const unsigned zebu_firsts[15][13];
extern const unsigned zebu_starts[21];
extern const unsigned zebu_defaults[1];
extern const unsigned zebu_EOFs[35];
extern const unsigned zebu_accepts[36];
#include <stddef.h>
struct zebu_state;
struct zebu_state* new_zebu_state();
void zebu_reset(struct zebu_state* this);
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length);
void zebu_parse_EOF(struct zebu_state* this);
void free_zebu_state(struct zebu_state* this);
