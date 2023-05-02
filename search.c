#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
bool overlap_for_leafnode(Rect* a, Rect b) {
    if (a->xh < b.xl || b.xh < a->xl || a->yh < b.yl || b.yh < a->yl) {
        return false;
    }
    return true;
}
bool overlap_for_internalnode(Rect a, Rect b) {
    if (a.xh < b.xl || b.xh < a.xl || a.yh < b.yl || b.yh < a.yl) {
        return false;
    }
    return true;
}

void search(RTreeNode* node, Rect search_this_rect) {
    if (node->isLeaf == true) {
        for (int i = 0; i <= node->data.leaf.max_hv ; i++) {
            if (overlap_for_leafnode(node->data.leaf.rect[i], search_this_rect)) {
                printf("(%d,%d)\n", node->data.leaf.rect[i]->xh, node->data.leaf.rect[i]->yh);
            }
        }
    }
    else {
        for (int i = 0; i <= node->data.internal.max_hv ; i++) {
            if (overlap_for_internalnode(node->data.internal.child[i]->data.internal.rect, search_this_rect)) {
                search(node->data.internal.child[i], search_this_rect);
            }
        }
    }
}
