#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
#define M 4
#define m 2

int *convertToBinary(int number)
{
    int binary[8];
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
        if (bin = 0)
        {
            binary[i] = 0;
        }

        binary[i] = bin % 10;
        bin /= 10;
    }

    return binary;
}

int *createInterleaf(int x_binary[8], int y_binary[8])
{
    int interleafBinary[16];

    for (int i = 0; i < 16; i++)
    {
        if (i % 2 == 0)
        {
            interleafBinary[i] = x_binary[i / 2];
        }
        if (i % 2 == 1)
        {
            interleafBinary[i] = x_binary[i / 2];
        }
    }
    return interleafBinary;
}

int convertToDecimal(int *interleaf)
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

void FindHilbertValue(Rect rectangle)
{
    int x_mid = (rectangle.xh + rectangle.xl) / 2;
    int y_mid = (rectangle.yh + rectangle.yl) / 2;

    int x_binary[8] = convertToBinary(x_mid);
    int y_binary[8] = convertToBinary(y_mid);

    int interleaf[16] = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);

    rectangle.hilbertValue = hilbertValue;
}

void chooseLeaf(Rect rectangle)
{
}

void insert(RTreeNode root, Rect newRectangle)
{
}