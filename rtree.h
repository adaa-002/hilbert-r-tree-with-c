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
    struct rect *next;
} Rect;

typedef struct rTreeNode
{
    int max_hv;
    Rect rect;        // redundant?
    struct rTreeNode *child; // array
    struct rTreeNode *next;
    bool leaf; // level
    // numchildren
    // tuple id
    // parent

} RTreeNode;

// root struct
typedef struct rTreeRoot{
    int max_hv;
    Rect rect;        // redundant?
    struct rTreeNode *child; // array
    bool leaf; // level
    // numchildren
    // tuple id
    // parent
}RTreeRoot;

// bad idea ??? but datapoint
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
    // height
} RTree;
