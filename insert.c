#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
#define M 4
#define m 2

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
    int x_mid = (xmin+xmax) / 2;
    int y_mid = (ymin+ymax) / 2;

    // malloc not needed?

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

    // malloc not needed?

    int *x_binary = convertToBinary(x_mid);
    int *y_binary = convertToBinary(y_mid);

    int *interleaf = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);

    rectangle.hilbertValue = hilbertValue;
    return hilbertValue;
}
RTreeNode find_AppChild(int hilbertValue, RTreeNode N) // TO-DO, pass node
    {
        // traverse thro children and find one with least HV of the given node
        
       // N.data.internal.child

    } RTreeNode chooseLeaf(Rect rectangle) // scope?
{
    // if the tree is empty
    //  set n to a leaf and return

    // else set N

    // malloc
    RTreeNode N = tree.root;

    // if not leaf
    // find temp which is most appropriate child of N using lhv
    // if that is a leaf return
    // else do the same for its children
    do
    {
        if (N.isLeaf)
        {
            return N;
        }
        else
        {
            RTreeNode temp = find_AppChild(rectangle.hilbertValue, N);
            // RTreeNode *newChild = (RTreeNode *)malloc(sizeof(RTreeNode));
            // make a while loop while()
            N.data.internal.child[N.data.internal.numchildren] = temp.data.internal.child[0]; // not 0, HAS TO BE CALLED RECURSIVELY, FIND TEMP'S CHILD WITH LEAST HV
            N.data.internal.numchildren++;                                                    // idk when leaf lol
        }
    } while (!N.isLeaf);
    return N;
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
RTreeNode HandleOverflow(L, newRectangle)
{
    ;
}
void insert(RTreeNode root, Rect newRectangle)
{
    RTreeNode L = chooseLeaf(newRectangle); // malloc?
    int l_hv = FindHilbertValue(newRectangle);

    for (int i = 0; i < M; i++)
    {
        if (L.rects->next == NULL)
        {
            addRectToNode(L, newRectangle, l_hv);
            return L;
        }
        else
        {
            RTreeNode new_leaf = HandleOverflow(L, newRectangle);
        }
    }
}

// testing

// int main()
// {
//     int number1 = 15;
//     int *test1 = convertToBinary(number1);
//     for (int i = 0; i < 8; i++)
//     {
//         printf("%d ", test1[i]);
//     }
//     printf("\n");
//     int number2 = 0;
//     int *test2 = convertToBinary(number2);
//     for (int i = 0; i < 8; i++)
//     {
//         printf("%d ", test2[i]);
//     }
//     printf("\n");

//     int *interleaf = createInterleaf(test1, test2);
//     for (int i = 0; i < 16; i++)
//     {
//         printf("%d ", interleaf[i]);
//     }
//     printf("\n");

//     int hilbertValue = convertToDecimal(interleaf);
//     printf("%d ", hilbertValue);
//     printf("\n");
// }