#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
bool is_intersect(Rect a, Rect b) {
    if (a.xh < b.xl || b.xh < a.xl || a.yh < b.yl || b.yh < a.yl) {
        return false;
    }
    return true;
}

void search_rtree(RTreeNode* node, Rect search_rect) {
    if (node->isLeaf == true) {
        for (int i = 0; i < node->data.leaf.max_hv + 1; i++) {
            if (is_intersect(node->data.leaf.rect, search_rect)) {
                printf("(%d,%d)\n", node->data.leaf.rect.xh, node->data.leaf.rect.yh);
            }
        }
    }
    else {
        for (int i = 0; i < node->data.internal.max_hv + 1; i++) {
            if (is_intersect(node->data.internal.child[i]->data.internal.rect, search_rect)) {
                search_rtree(node->data.internal.child[i], search_rect);
            }
        }
    }
}
