#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define M 4
#define m 2

typedef struct point
{
    int x, y;
} Point;

typedef struct rect
{
    int xh, yh, xl, yl;
    int hilbertValue;
    Rect *next;
} Rect;

typedef struct rTreeNode
{
    int max_hv;
    Rect *rect;
    RTreeNode *child;
    RTreeNode *next;
} RTreeNode;

typedef struct rTreeLeaf
{
    int max_hv;
    Rect *rect;
    Point *pt;
} RTreeLeaf;

typedef struct rTree
{
    RTreeNode *root;
    int num_nodes;
    int split_distribution;
}RTree;
