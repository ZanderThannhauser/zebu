const unsigned zebu_shifts[14][13] = {
	[1][2] = 3,
	[1][3] = 2,
	[1][9] = 5,
	[1][10] = 4,
	[1][11] = 15,
	[1][12] = 9,
	[3][2] = 3,
	[3][3] = 2,
	[3][9] = 5,
	[3][10] = 4,
	[3][11] = 13,
	[3][12] = 9,
	[5][5] = 6,
	[5][8] = 8,
	[6][2] = 3,
	[6][3] = 2,
	[6][9] = 5,
	[6][12] = 7,
	[8][2] = 3,
	[8][3] = 2,
	[8][9] = 5,
	[8][12] = 7,
	[9][6] = 10,
	[9][7] = 12,
	[10][2] = 3,
	[10][3] = 2,
	[10][9] = 5,
	[10][10] = 11,
	[10][12] = 9,
	[12][2] = 3,
	[12][3] = 2,
	[12][9] = 5,
	[12][10] = 11,
	[12][12] = 9,
	[13][4] = 14,
};
const unsigned zebu_reduces[16][9] = {
	[2][1] = 9,
	[2][4] = 9,
	[2][5] = 9,
	[2][6] = 9,
	[2][7] = 9,
	[2][8] = 9,
	[4][1] = 11,
	[4][4] = 11,
	[5][1] = 12,
	[5][4] = 12,
	[5][6] = 12,
	[5][7] = 12,
	[7][1] = 12,
	[7][4] = 12,
	[7][6] = 12,
	[7][7] = 12,
	[9][1] = 10,
	[9][4] = 10,
	[11][1] = 10,
	[11][4] = 10,
	[14][1] = 9,
	[14][4] = 9,
	[14][5] = 9,
	[14][6] = 9,
	[14][7] = 9,
	[14][8] = 9,
	[15][1] = 13,
};
const unsigned zebu_lexer[17][58] = {
	[1][40] = 2,
	[1][48] = 3,
	[1][49] = 3,
	[1][50] = 3,
	[1][51] = 3,
	[1][52] = 3,
	[1][53] = 3,
	[1][54] = 3,
	[1][55] = 3,
	[1][56] = 3,
	[1][57] = 3,
	[3][48] = 3,
	[3][49] = 3,
	[3][50] = 3,
	[3][51] = 3,
	[3][52] = 3,
	[3][53] = 3,
	[3][54] = 3,
	[3][55] = 3,
	[3][56] = 3,
	[3][57] = 3,
	[4][41] = 5,
	[4][42] = 6,
	[4][43] = 7,
	[4][45] = 8,
	[4][47] = 9,
	[10][41] = 11,
	[12][41] = 13,
	[12][43] = 14,
	[12][45] = 15,
	[16][41] = 17,
};
const unsigned zebu_firsts[14][13] = {
	[9][2] = 1,
	[9][3] = 1,
	[10][2] = 1,
	[10][3] = 1,
	[10][12] = 1,
	[11][2] = 1,
	[11][3] = 1,
	[11][10] = 1,
	[12][2] = 1,
	[12][3] = 1,
	[12][9] = 1,
	[13][2] = 1,
	[13][3] = 1,
	[13][11] = 1,
};
const unsigned zebu_starts[16] = {
	[1] = 1,
	[2] = 4,
	[3] = 1,
	[4] = 10,
	[5] = 4,
	[6] = 1,
	[7] = 12,
	[8] = 1,
	[9] = 12,
	[10] = 1,
	[11] = 10,
	[12] = 1,
	[13] = 16,
	[14] = 4,
	[15] = 18,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_accepts[18] = {
	[2] = 2,
	[3] = 3,
	[5] = 4,
	[6] = 5,
	[7] = 6,
	[8] = 7,
	[9] = 8,
	[11] = 4,
	[13] = 4,
	[14] = 6,
	[15] = 7,
	[17] = 4,
};
const char* zebu_grammar_names[15] = {
	[13] = "(start)",
	[10] = "add",
	[9] = "lit",
	[12] = "mul",
	[11] = "root",
};
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
struct zebu_state { unsigned* data, n, cap, lstate; };
static void push(struct zebu_state* this, unsigned ystate) {
	if (this->n + 1 >= this->cap) {
		this->cap = this->cap << 1 ?: 1;
		this->data = realloc(this->data, sizeof(*this->data) * this->cap);
	}
	this->data[this->n++] = ystate;
}
static void ddprintf(struct zebu_state* this, const char* fmt, ...) {
	for (unsigned i = 0, n = this->n; i < n; i++) 
		printf("%u ", this->data[i]);
	printf("| ");
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}
struct zebu_state* new_zebu_state() {
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->data = NULL, this->n = 0, this->cap = 0;
	this->lstate = 1;
	push(this, 1);
	return this;
}
void zebu_reset(struct zebu_state* this) {
	this->n = 0;
	this->lstate = 1;
	push(this, 1);
}
#define N(array) (sizeof(array) / sizeof(*array))
static void process_token(struct zebu_state* this, unsigned t) {
	unsigned b, d, y = this->data[this->n - 1];
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t]))) {
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t])) {
		ddprintf(this, "b == %u\n", b);
			unsigned s = t;
			while (!(1
				 && y < N(zebu_shifts) && b < N(*zebu_shifts) && (d = zebu_shifts[y][b])
				 && b < N(zebu_firsts) && s < N(*zebu_firsts) && (    zebu_firsts[b][s]))) {
				if (this->n == 1) return;
				s = this->data[--this->n - 1];
				y = this->data[--this->n - 1];
				ddprintf(this, "y == %u\n", y);
			}
			push(this, b), push(this, d), y = d;
			ddprintf(this, "y == %u\n", y);
		} else {
			assert(!"TODO");
			exit(1);
		}
	}
	push(this, t), push(this, b), y = b;
}
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length) {
	unsigned a, b, c, l = this->lstate;
	while (c = *text++, length--) {
		ddprintf(this, "c == %c\n", c);
		while (!(a = c < N(*zebu_lexer) ? zebu_lexer[l][c] : l < N(zebu_defaults) ? zebu_defaults[l] : 0)) {
			if (l < N(zebu_accepts) && (b = zebu_accepts[l])) {
				process_token(this, b);
				l = zebu_starts[this->data[this->n - 1]];
				ddprintf(this, "l == %u\n", l);
			} else {
				assert(!"TODO");
				exit(1);
			}
		}
		l = a;
		ddprintf(this, "l == %u\n", l);
	}
	this->lstate = l;
}
void zebu_parse_EOF(struct zebu_state* this) {
	unsigned b, l = this->lstate;
	ddprintf(this, "l == %u\n", l);
	if (l < N(zebu_accepts) && (b = zebu_accepts[l])) {
		process_token(this, b);
	} else {
		assert(!"TODO");
		exit(1);
	}
	process_token(this, 1);
}
void free_zebu_state(struct zebu_state* this) {
	free(this->data);
	free(this);
}
