void preorder_traversal(RTreeNode* node) {
    if (node != NULL) {
        // Print the bounds of this node
        printf("[");
        printf("%d %d %d %d", node->data.internal.rect.xh, node->data.internal.rect.yh, node->data.internal.rect.xl, node->data.internal.rect.yl);
        printf("]\n");
        // Recursively traverse the children of this node
        if (node->isLeaf == true) {
            for (int i = 0; i < node->data.leaf.max_hv + 1; i++) {
                printf("    (%d,%d)\n", node->data.leaf.rect.xh, node->data.leaf.rect.yh);
            }
        }
        else {
            for (int i = 0; i < node->data.internal.max_hv + 1; i++) {
                pre_order_traversal(node->data.internal.child[i]);
            }
        }
    }
}
