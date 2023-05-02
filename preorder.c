#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
void preorder(RTreeNode* node) {
    if (node != NULL) {
        
        printf("This is internal node");
        printf("%d %d %d %d", node->data.internal.rect.xh, node->data.internal.rect.yh, node->data.internal.rect.xl, node->data.internal.rect.yl);
        
        if (node->isLeaf == true) {
            for (int i = 0; i <= node->data.leaf.max_hv; i++) {
                printf("This is leaf node");
                printf("(%d,%d)\n", node->data.leaf.rect[i]->xh, node->data.leaf.rect[i]->yh);
            }
        }
        else {
            for (int i = 0; i <= node->data.internal.max_hv ; i++) {
                preorder(node->data.internal.child[i]);
            }
        }
    }
}
