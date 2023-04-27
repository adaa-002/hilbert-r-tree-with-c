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
    struct rect* next;//no
}Rect;
typedef struct rTreeNode
{
    int max_hv;
    Rect* rects; //head
    bool isLeaf;
    //next?
    union
    {
        LeafNode leaf;
        InternalNode internal;
    } data;
   
    // numchildren
    // tuple id
    // parent
} RTreeNode;

typedef struct internalNode
{
    int max_hv;
    Rect rect;                  
    struct rTreeNode *child; //hell
    struct rTreeNode *next;
    bool isLeaf; // level
    int numchildren;
    // tuple id
    // parent

} InternalNode;

typedef struct leafNode
{
    int max_hv;
    Rect rect;
    //Point* childOfleaf;
} LeafNode;

typedef struct rTree
{
    RTreeNode root; // ptr?
    int num_nodes;
    int split_distribution;
    // height
} RTree;

RTree tree;