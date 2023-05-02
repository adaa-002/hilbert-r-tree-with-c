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
    struct rect* next;
}Rect;

typedef struct internalNode
{
    int max_hv;
    Rect rect;                  
    struct rTreeNode *child[M]; //hell
    struct rTreeNode *next;
    bool isLeaf; // level
    int numchildren;  //we need this field, please update this in the insert function
    // tuple id
} InternalNode;

typedef struct leafNode
{
    int max_hv;
    Rect *rect[M];
    //Point* childOfleaf;
} LeafNode;

typedef struct rTreeNode
{
    int max_hv;
    Rect* rects; //head
    bool isLeaf;
    struct rTreeNode* parent;
    union
    {
        struct leafNode leaf;
        struct internalNode internal;
    } data;
   
    int numchildren;
    // tuple id
} RTreeNode;



typedef struct rTree
{
    RTreeNode root; // ptr?
    int num_nodes;
    int split_distribution;
    // height
} RTree;

RTree tree;