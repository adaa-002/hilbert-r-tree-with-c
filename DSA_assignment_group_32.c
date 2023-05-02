#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define M 4
#define m 2

typedef struct rect
{
    int xh, yh, xl, yl;
    int hilbertValue;
    struct rect *next;
} Rect;

typedef struct internalNode
{
    int max_hv;
    Rect rect;
    struct rTreeNode *child[M];
    struct rTreeNode *next;
    bool isLeaf;
    int numchildren;
} InternalNode;

typedef struct leafNode
{
    int max_hv;
    Rect *rect[M];
} LeafNode;

typedef struct rTreeNode
{
    int max_hv;
    Rect *rects;
    bool isLeaf;
    struct rTreeNode *parent;
    int numchildren;
    union
    {
        struct leafNode leaf;
        struct internalNode internal;
    } data;
    // tuple id
} RTreeNode;

typedef struct rTree
{
    RTreeNode root;
    int num_nodes;
} RTree;

RTree tree;

int *convertToBinary(int number) // tested
{
    int *binary = (int *)malloc(8 * sizeof(int));
    int bin = 0, i = 1, rem = 0;
    while (number != 0)
    {
        rem = number % 2;
        number /= 2;
        bin += rem * i;
        i *= 10;
    }
    for (int i = 7; i >= 0; i--)
    {
        if (bin == 0)
        {
            binary[i] = 0;
        }

        binary[i] = bin % 10;
        bin /= 10;
    }

    return binary;
}

int *createInterleaf(int x_binary[8], int y_binary[8]) // tested
{
    int *interleafBinary = (int *)malloc(16 * sizeof(int));

    for (int i = 0; i < 16; i++)
    {
        if (i % 2 == 0)
        {
            interleafBinary[i] = x_binary[i / 2];
        }
        if (i % 2 == 1)
        {
            interleafBinary[i] = y_binary[i / 2];
        }
    }
    return interleafBinary;
}

int convertToDecimal(int *interleaf) // tested
{
    int hilbertValue = 0;
    for (int i = 15; i >= 0; i--)
    {
        if (interleaf[i] == 1)
        {
            hilbertValue += pow(2, 15 - i);
        }
    }
    return hilbertValue;
}

int FindHilbertValueNode(Rect *rectangles)
{
    int temp, xmin, xmax, ymin, ymax;
    xmin = rectangles->xl;
    xmax = rectangles->xh;
    ymin = rectangles->yl;
    ymax = rectangles->yh;
    do
    {
        rectangles++;
        if (xmin > rectangles->xl)
        {
            xmin = rectangles->xl;
        }
        if (xmax < rectangles->xh)
        {
            xmax = rectangles->xh;
        }
        if (ymin > rectangles->yl)
        {
            ymin = rectangles->yl;
        }
        if (ymax < rectangles->yh)
        {
            ymax = rectangles->yh;
        }
    } while (rectangles != NULL);
    int x_mid = (xmin + xmax) / 2;
    int y_mid = (ymin + ymax) / 2;

    int *x_binary = convertToBinary(x_mid);
    int *y_binary = convertToBinary(y_mid);

    int *interleaf = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);
    return hilbertValue;
}

int FindHilbertValue(Rect rectangle)
{
    int x_mid = (rectangle.xh + rectangle.xl) / 2;
    int y_mid = (rectangle.yh + rectangle.yl) / 2;

    int *x_binary = convertToBinary(x_mid);
    int *y_binary = convertToBinary(y_mid);

    int *interleaf = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);

    rectangle.hilbertValue = hilbertValue;
    return hilbertValue;
}

int find_AppChild(int hilbertValue, RTreeNode N)
{
    // traverse thro children and find one with least HV of the given node
    int i = 0, key;
    int lhv = FindHilbertValueNode(N.data.internal.child[0]);
    do
    {
        int temp = FindHilbertValueNode(N.data.internal.child[i]);
        if (temp < lhv)
        {
            lhv = temp;
            key = i;
        }
        i++;
    } while (N.data.internal.child[i] != NULL);
    return key;
}

RTreeNode *chooseLeaf(Rect rectangle)
{
    RTreeNode *N = (RTreeNode *)malloc(sizeof(RTreeNode));
    N = &tree.root;

    RTreeNode *temp = (RTreeNode *)malloc(sizeof(RTreeNode));
    while (!N->isLeaf)
    {
        int key = find_AppChild(rectangle.hilbertValue, *N);

        temp = N->data.internal.child[key];
        N = temp;
    }
    return &N;
}

void addRectToNode(RTreeNode L, Rect newRectangle, int l_hv)
{
    Rect *curr, *temp;
    temp = L.rects;
    curr = L.rects;

    do
    {
        temp++;

        if (temp->hilbertValue > l_hv)
        {
            curr = &newRectangle;
            newRectangle.next = temp;
        }
        else
        {
            curr = temp;
        }

        if (temp->next == NULL)
        {
            curr->next = &newRectangle;
            newRectangle.next = NULL;
        }
    } while (temp->next != NULL);
}

void merge(Rect arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Rect L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].hilbertValue <= R[j].hilbertValue)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Rect arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

RTreeNode *HandleOverflow(RTreeNode *L, Rect newRectangle)
{
    Rect Rects[17]; // array to store all the children rectangles
    int count = 0;

    RTreeNode *Parent = L->parent;

    for (int i = 0; i < Parent->numchildren; i++) // traverse through all children of parent
    {
        for (int j = 0; j < Parent[i].numchildren; j++)
        {
            Rects[count] = Parent[i].rects[j];
            count++;
        }
    }

    Rects[count] = newRectangle; // add new rectangle to array

    if (Parent->numchildren != M)
    {
        Parent[Parent->numchildren + 1]->rects = newRectangle;
        Parent->numchildren++;
        mergeSort(Parent->rects, 0, Parent->numchildren);
    }

    mergeSort(Rects, 0, count); // sort rectangles

    int x = 0;

    for (int i = 0; i < Parent->numchildren; i++)
    {
        for (int j = 0; j < Parent[i].numchildren && x < count; j++) // add rectangles to children in asc order of HV
        {
            Parent[i].rects[j] = Rects[x];
            x++;
        }
    }
    if (count == 17)
    {
        RTreeNode *NN;
        NN->rects[0] = Rects[16]; // Add new rectangle to the newly created node
        NN->parent = Parent;      // Add newly created node to Parent
        return NN;
    }
    else
    {
        return NULL;
    }
}

void AdjustTree(RTreeNode *N, RTreeNode *NN)
{
    RTreeNode *Np = (RTreeNode *)malloc(sizeof(RTreeNode));
    RTreeNode *temp = (RTreeNode *)malloc(sizeof(RTreeNode));
    RTreeNode *PP = (RTreeNode *)malloc(sizeof(RTreeNode));

    int full = 0;

    while (NN->parent != NULL)
    {
        // A1
        if (NN->parent == NULL)
        {
            return;
        }

        // A2
        Np = N->parent;
        if (NN != NULL)
        {

            if (Np->data.internal.child[0] == NULL || Np->data.internal.child[1] == NULL || Np->data.internal.child[2] == NULL || Np->data.internal.child[3] == NULL)
            {
                full = 1;
            }

            if (full)
            {
                PP = HandleOverflow(Np, *NN->rects);
            }
            // insert NN in Np
            int hv_Np = FindHilbertValueNode(Np->rects);
            int key = find_AppChild(hv_Np, *Np); //??????

            temp = Np->data.internal.child[key];
            NN = temp;
        }

        // A3
        RTreeNode *Np_parent, *Np_parent_child;

        Np_parent = Np->parent;
        int i = 0;
        do
        {
            Np_parent_child = Np_parent->data.internal.child[i];
            Np_parent_child->max_hv = FindHilbertValueNode(Np_parent_child->rects);
            i++;

        } while (Np_parent_child != NULL);

        // A4
        if (full)
        {
            NN = PP;
        }
    }
}

void insert(RTreeNode root, Rect newRectangle)
{
    RTreeNode *L = chooseLeaf(newRectangle);
    RTreeNode *NN = (RTreeNode *)malloc(sizeof(RTreeNode));
    int l_hv = FindHilbertValue(newRectangle);

    for (int i = 0; i < M; i++)
    {
        if (L->rects->next == NULL)
        {
            addRectToNode(*L, newRectangle, l_hv);
        }
        else
        {
            NN = HandleOverflow(L, newRectangle);
        }
    }
    AdjustTree(L, NN);

    RTreeNode *new_root = (RTreeNode *)malloc(sizeof(RTreeNode));
    bool root_split = true;
    if (root_split)
    {
        new_root->data.internal.child[0] = &tree.root;
        new_root->data.internal.child[1] = &NN;
        new_root->parent = NULL;
        tree.root = *new_root;
    }
}

bool overlap_for_leafnode(Rect *a, Rect b)
{
    if (a->xh < b.xl || b.xh < a->xl || a->yh < b.yl || b.yh < a->yl)
    {
        return false;
    }
    return true;
}

bool overlap_for_internalnode(Rect a, Rect b)
{
    if (a.xh < b.xl || b.xh < a.xl || a.yh < b.yl || b.yh < a.yl)
    {
        return false;
    }
    return true;
}

void search(RTreeNode *node, Rect search_this_rect)
{
    if (node->isLeaf == true)
    {
        for (int i = 0; i <= node->data.leaf.max_hv; i++)
        {
            if (overlap_for_leafnode(node->data.leaf.rect[i], search_this_rect))
            {
                printf("(%d,%d)\n", node->data.leaf.rect[i]->xh,
                       node->data.leaf.rect[i]->yh);
            }
        }
    }
    else
    {
        for (int i = 0; i <= node->data.internal.max_hv; i++)
        {
            if (overlap_for_internalnode(node->data.internal.child[i]->data.internal.rect,
                                         search_this_rect))
            {
                search(node->data.internal.child[i], search_this_rect);
            }
        }
    }
}

int main()
{
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open file");
        exit(1);
    }

    RTreeNode *root = (RTreeNode *)malloc(sizeof(RTreeNode));
    root = tree.root;
    int x, y;
    while (fscanf(fp, "%d %d", &x, &y) != EOF)
    {
        Rect *rectToInsert = (Rect *)malloc(sizeof(Rect));
        rectToInsert->xh = x;
        rectToInsert->xl = x;
        rectToInsert->yh = y;
        rectToInsert->yl = y;
        insert(x, y)
    }
    fclose(fp);

    printf("Chose an option from the below menu \n");
    printf("1. Insertion: Give a new rectangle to add to the RTree, in the format of xmin, xmax, ymin and ymax\n");
    printf("2. Search: Give a reactangle in the format of xmin, xmax, ymin and ymax to search for \n");
    printf("3. PreOrderTraversal : Prints the R Tree") int option;
    scanf("Enter your option (1,2,3): %d \n", option);

    switch (option)
    {
    case 1:
        Rect *rectToInsert = (Rect *)malloc(sizeof(Rect));
        scanf("Enter xmin, xmax, ymin, ymax %d%d%d%d", rectToInsert->xl, rectToInsert->xh, rectToInsert->yl, rectToInsert->yh);
        insert(root, rectToInsert);
        break;

    case2:
        Rect *rectToSearch = (Rect *)malloc(sizeof(Rect));
        scanf("Enter xmin, xmax, ymin, ymax %d%d%d%d", rectToSearch->xl, rectToSearch->xh, rectToSearch->yl, rectToSearch->yh);
        search(root,rectToSearch);
        break;
    case3:
        preorder(root);
        break:
    }
}