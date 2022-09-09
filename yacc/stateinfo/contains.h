
#include <stdbool.h>

struct stateinfo;
struct trie;

bool stateinfo_contains(
	struct stateinfo* this,
	struct trie* trie);
