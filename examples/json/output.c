const unsigned zebu_shifts[19][14] = {
	[1][2] = 5,
	[1][3] = 4,
	[1][4] = 6,
	[1][5] = 3,
	[1][6] = 2,
	[1][7] = 7,
	[1][12] = 20,
	[6][2] = 5,
	[6][3] = 4,
	[6][4] = 6,
	[6][5] = 3,
	[6][6] = 2,
	[6][7] = 7,
	[6][12] = 16,
	[7][2] = 8,
	[8][13] = 9,
	[9][2] = 5,
	[9][3] = 4,
	[9][4] = 6,
	[9][5] = 3,
	[9][6] = 2,
	[9][7] = 7,
	[9][12] = 10,
	[10][8] = 11,
	[10][10] = 15,
	[11][2] = 12,
	[12][13] = 13,
	[13][2] = 5,
	[13][3] = 4,
	[13][4] = 6,
	[13][5] = 3,
	[13][6] = 2,
	[13][7] = 7,
	[13][12] = 14,
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
	[17][12] = 18,
	[18][8] = 17,
	[18][9] = 19,
};
const unsigned zebu_reduces[21][12] = {
	[2][8] = 12,
	[2][9] = 12,
	[2][10] = 12,
	[2][11] = 12,
	[3][8] = 12,
	[3][9] = 12,
	[3][10] = 12,
	[3][11] = 12,
	[4][8] = 12,
	[4][9] = 12,
	[4][10] = 12,
	[4][11] = 12,
	[5][8] = 12,
	[5][9] = 12,
	[5][10] = 12,
	[5][11] = 12,
	[15][8] = 12,
	[15][9] = 12,
	[15][10] = 12,
	[15][11] = 12,
	[19][8] = 12,
	[19][9] = 12,
	[19][10] = 12,
	[19][11] = 12,
	[20][11] = 14,
};
const unsigned zebu_lexer[35][126] = {
	[1][32] = 1,
	[1][34] = 2,
	[1][48] = 5,
	[1][49] = 5,
	[1][50] = 5,
	[1][51] = 5,
	[1][52] = 5,
	[1][53] = 5,
	[1][54] = 5,
	[1][55] = 5,
	[1][56] = 5,
	[1][57] = 5,
	[1][91] = 6,
	[1][102] = 7,
	[1][116] = 12,
	[1][123] = 16,
	[2][97] = 3,
	[2][98] = 3,
	[2][99] = 3,
	[2][100] = 3,
	[2][101] = 3,
	[2][102] = 3,
	[2][103] = 3,
	[2][104] = 3,
	[2][105] = 3,
	[2][106] = 3,
	[2][107] = 3,
	[2][108] = 3,
	[2][109] = 3,
	[2][110] = 3,
	[2][111] = 3,
	[2][112] = 3,
	[2][113] = 3,
	[2][114] = 3,
	[2][115] = 3,
	[2][116] = 3,
	[2][117] = 3,
	[2][118] = 3,
	[2][119] = 3,
	[2][120] = 3,
	[2][121] = 3,
	[2][122] = 3,
	[3][34] = 4,
	[3][97] = 3,
	[3][98] = 3,
	[3][99] = 3,
	[3][100] = 3,
	[3][101] = 3,
	[3][102] = 3,
	[3][103] = 3,
	[3][104] = 3,
	[3][105] = 3,
	[3][106] = 3,
	[3][107] = 3,
	[3][108] = 3,
	[3][109] = 3,
	[3][110] = 3,
	[3][111] = 3,
	[3][112] = 3,
	[3][113] = 3,
	[3][114] = 3,
	[3][115] = 3,
	[3][116] = 3,
	[3][117] = 3,
	[3][118] = 3,
	[3][119] = 3,
	[3][120] = 3,
	[3][121] = 3,
	[3][122] = 3,
	[5][48] = 5,
	[5][49] = 5,
	[5][50] = 5,
	[5][51] = 5,
	[5][52] = 5,
	[5][53] = 5,
	[5][54] = 5,
	[5][55] = 5,
	[5][56] = 5,
	[5][57] = 5,
	[7][97] = 8,
	[8][108] = 9,
	[9][115] = 10,
	[10][101] = 11,
	[12][114] = 13,
	[13][117] = 14,
	[14][101] = 15,
	[17][32] = 17,
	[17][44] = 18,
	[17][93] = 19,
	[17][125] = 20,
	[22][32] = 22,
	[22][34] = 23,
	[23][97] = 24,
	[23][98] = 24,
	[23][99] = 24,
	[23][100] = 24,
	[23][101] = 24,
	[23][102] = 24,
	[23][103] = 24,
	[23][104] = 24,
	[23][105] = 24,
	[23][106] = 24,
	[23][107] = 24,
	[23][108] = 24,
	[23][109] = 24,
	[23][110] = 24,
	[23][111] = 24,
	[23][112] = 24,
	[23][113] = 24,
	[23][114] = 24,
	[23][115] = 24,
	[23][116] = 24,
	[23][117] = 24,
	[23][118] = 24,
	[23][119] = 24,
	[23][120] = 24,
	[23][121] = 24,
	[23][122] = 24,
	[24][34] = 25,
	[24][97] = 24,
	[24][98] = 24,
	[24][99] = 24,
	[24][100] = 24,
	[24][101] = 24,
	[24][102] = 24,
	[24][103] = 24,
	[24][104] = 24,
	[24][105] = 24,
	[24][106] = 24,
	[24][107] = 24,
	[24][108] = 24,
	[24][109] = 24,
	[24][110] = 24,
	[24][111] = 24,
	[24][112] = 24,
	[24][113] = 24,
	[24][114] = 24,
	[24][115] = 24,
	[24][116] = 24,
	[24][117] = 24,
	[24][118] = 24,
	[24][119] = 24,
	[24][120] = 24,
	[24][121] = 24,
	[24][122] = 24,
	[26][32] = 26,
	[26][58] = 27,
	[28][32] = 28,
	[28][44] = 29,
	[28][125] = 30,
	[31][32] = 31,
	[31][44] = 32,
	[31][93] = 33,
	[34][32] = 34,
};
const unsigned zebu_firsts[15][13] = {
	[12][2] = 1,
	[12][3] = 1,
	[12][4] = 1,
	[12][5] = 1,
	[12][6] = 1,
	[12][7] = 1,
	[14][2] = 1,
	[14][3] = 1,
	[14][4] = 1,
	[14][5] = 1,
	[14][6] = 1,
	[14][7] = 1,
	[14][12] = 1,
};
const unsigned zebu_starts[21] = {
	[1] = 1,
	[2] = 17,
	[3] = 17,
	[4] = 17,
	[5] = 17,
	[6] = 1,
	[7] = 22,
	[8] = 26,
	[9] = 1,
	[10] = 28,
	[11] = 22,
	[12] = 26,
	[13] = 1,
	[14] = 28,
	[15] = 17,
	[16] = 31,
	[17] = 1,
	[18] = 31,
	[19] = 17,
	[20] = 34,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[35] = {
	[17] = 21,
	[34] = 35,
};
const unsigned zebu_accepts[36] = {
	[4] = 2,
	[5] = 3,
	[6] = 4,
	[11] = 5,
	[15] = 6,
	[16] = 7,
	[18] = 8,
	[19] = 9,
	[20] = 10,
	[21] = 11,
	[25] = 2,
	[27] = 13,
	[29] = 8,
	[30] = 10,
	[32] = 8,
	[33] = 9,
	[35] = 11,
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
	unsigned i = this->l.n, n = i, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	while (1) {
		assert(i <= n + 1);
		if (i < n) {
			c = this->l.data[i];
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		} else {
			a = l < N(zebu_EOFs) ? zebu_EOFs[l] : 0;
		}
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
}
void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
