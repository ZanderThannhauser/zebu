
#include "R_DEPTH.h"
#include "L_DEPTH.h"

#include "check_balance.h"

int avl_check_balance(avl_node_t *avlnode) {
	int d;
	d = R_DEPTH(avlnode) - L_DEPTH(avlnode);
	return d<-1?-1:d>1?1:0;
}

