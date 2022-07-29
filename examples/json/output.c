const unsigned zebu_shifts[19][13] = {
	[1][2] = 5,
	[1][3] = 4,
	[1][4] = 6,
	[1][5] = 3,
	[1][6] = 2,
	[1][7] = 7,
	[1][11] = 20,
	[6][2] = 5,
	[6][3] = 4,
	[6][4] = 6,
	[6][5] = 3,
	[6][6] = 2,
	[6][7] = 7,
	[6][11] = 16,
	[7][2] = 8,
	[8][12] = 9,
	[9][2] = 5,
	[9][3] = 4,
	[9][4] = 6,
	[9][5] = 3,
	[9][6] = 2,
	[9][7] = 7,
	[9][11] = 10,
	[10][8] = 11,
	[10][10] = 15,
	[11][2] = 12,
	[12][12] = 13,
	[13][2] = 5,
	[13][3] = 4,
	[13][4] = 6,
	[13][5] = 3,
	[13][6] = 2,
	[13][7] = 7,
	[13][11] = 14,
	[14][8] = 11,
	[14][10] = 15,
	[16][8] = 17,
	[16][9] = 19,
	[17][2] = 5,
	[17][3] = 4,
	[17][4] = 6,
	[17][5] = 3,
	[17][6] = 2,
	[17][7] = 7,
	[17][11] = 18,
	[18][8] = 17,
	[18][9] = 19,
};
const unsigned zebu_reduces[21][11] = {
	[2][1] = 11,
	[2][8] = 11,
	[2][9] = 11,
	[2][10] = 11,
	[3][1] = 11,
	[3][8] = 11,
	[3][9] = 11,
	[3][10] = 11,
	[4][1] = 11,
	[4][8] = 11,
	[4][9] = 11,
	[4][10] = 11,
	[5][1] = 11,
	[5][8] = 11,
	[5][9] = 11,
	[5][10] = 11,
	[15][1] = 11,
	[15][8] = 11,
	[15][9] = 11,
	[15][10] = 11,
	[19][1] = 11,
	[19][8] = 11,
	[19][9] = 11,
	[19][10] = 11,
	[20][1] = 13,
};
const unsigned zebu_lexer[31][126] = {
	[1][34] = 2,
	[1][48] = 5,
	[1][49] = 5,
	[1][50] = 5,
	[1][51] = 5,
	[1][91] = 6,
	[1][102] = 7,
	[1][116] = 12,
	[1][123] = 16,
	[2][97] = 3,
	[2][98] = 3,
	[2][99] = 3,
	[3][34] = 4,
	[3][97] = 3,
	[3][98] = 3,
	[3][99] = 3,
	[5][48] = 5,
	[5][49] = 5,
	[5][50] = 5,
	[5][51] = 5,
	[7][97] = 8,
	[8][108] = 9,
	[9][115] = 10,
	[10][101] = 11,
	[12][114] = 13,
	[13][117] = 14,
	[14][101] = 15,
	[17][44] = 18,
	[17][93] = 19,
	[17][125] = 20,
	[21][34] = 22,
	[22][97] = 23,
	[22][98] = 23,
	[22][99] = 23,
	[23][34] = 24,
	[23][97] = 23,
	[23][98] = 23,
	[23][99] = 23,
	[25][58] = 26,
	[27][44] = 28,
	[27][125] = 29,
	[30][44] = 31,
	[30][93] = 32,
};
const unsigned zebu_firsts[14][12] = {
	[11][2] = 1,
	[11][3] = 1,
	[11][4] = 1,
	[11][5] = 1,
	[11][6] = 1,
	[11][7] = 1,
	[13][2] = 1,
	[13][3] = 1,
	[13][4] = 1,
	[13][5] = 1,
	[13][6] = 1,
	[13][7] = 1,
	[13][11] = 1,
};
const unsigned zebu_starts[21] = {
	[1] = 1,
	[2] = 17,
	[3] = 17,
	[4] = 17,
	[5] = 17,
	[6] = 1,
	[7] = 21,
	[8] = 25,
	[9] = 1,
	[10] = 27,
	[11] = 21,
	[12] = 25,
	[13] = 1,
	[14] = 27,
	[15] = 17,
	[16] = 30,
	[17] = 1,
	[18] = 30,
	[19] = 17,
	[20] = 33,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_accepts[33] = {
	[4] = 2,
	[5] = 3,
	[6] = 4,
	[11] = 5,
	[15] = 6,
	[16] = 7,
	[18] = 8,
	[19] = 9,
	[20] = 10,
	[24] = 2,
	[26] = 12,
	[28] = 8,
	[29] = 10,
	[31] = 8,
	[32] = 9,
};
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
struct zebu_state {
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};
static void push(struct zebu_state* this, unsigned ystate) {
	if (this->y.n + 1 >= this->y.cap) {
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
	}
	this->y.data[this->y.n++] = ystate;
}
static void append(struct zebu_state* this, const unsigned char* text, size_t length) {
	while (this->l.n + length >= this->l.cap) {
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	memcpy(this->l.data + this->l.n, text, length);
	this->l.n += length;
}
struct zebu_state* new_zebu_state() {
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}
void zebu_reset(struct zebu_state* this) {
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
}
#define N(array) (sizeof(array) / sizeof(*array))
static void process_token(struct zebu_state* this, unsigned t) {
	unsigned b, d, y = this->y.data[this->y.n - 1];
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t]))) {
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t])) {
			unsigned s = t;
			while (!(1
				 && y < N(zebu_shifts) && b < N(*zebu_shifts) && (d = zebu_shifts[y][b])
				 && b < N(zebu_firsts) && s < N(*zebu_firsts) && (    zebu_firsts[b][s]))) {
				if (this->y.n == 1) return;
				s = this->y.data[--this->y.n - 1];
				y = this->y.data[--this->y.n - 1];
			}
			push(this, b), push(this, d), y = d;
		} else {
			assert(!"TODO");
			exit(1);
		}
	}
	push(this, t), push(this, b), y = b;
}
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length) {
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	i = this->l.n;
	append(this, text, length);
	for (n = this->l.n, f = 0; i < n;) {
		c = this->l.data[i];
		a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		if (a) {
			if (b)
				l = a, t = b, f = i++;
			else
				l = a, i++;
		} else if (b) {
			process_token(this, b);
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
		} else if (t) {
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		} else {
			assert(!"TODO");
		}
	}
	memcpy(this->l.data, this->l.data + f, this->l.n = n - f);
	this->t = t;
	this->lstate = l;
}
void zebu_parse_EOF(struct zebu_state* this) {
	unsigned i, n, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	for (i = this->l.n, n = i; ; ) {
		assert(i <= n);
		if (i < n) {
			c = this->l.data[i];
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		} else a = 0;
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		if (a) {
			if (b)
				l = a, t = b, f = i++;
			else
				l = a, i++;
		} else if (b) {
			process_token(this, b);
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
			if (f >= n) break;
		} else if (t) {
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		} else {
			assert(!"TODO");
		}
	}
	process_token(this, 1);
}
void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
