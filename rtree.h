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
    struct rect* next; //no // I don't think we need this anywhere -Bharat
}Rect;

typedef struct rTreeNode
{
    int max_hv;
    Rect* rects; //head
    bool isLeaf;
    //next?
    RTreeNode* parent;
    union
    {
        LeafNode leaf;
        InternalNode internal;
    } data;
   
    int numchildren;
    // tuple id
    // parent
} RTreeNode;

typedef struct internalNode
{
    int max_hv;
    Rect rect;                  
    struct rTreeNode *child[M]; //hell
    struct rTreeNode *next;
    bool isLeaf; // level
    int numchildren;  //we need this field, please update this in the insert function
    // tuple id
    // parent

} InternalNode;

typedef struct leafNode
{
    int max_hv;
    Rect *rect[M];
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