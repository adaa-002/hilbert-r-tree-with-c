#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct point
{
    int x, y;
} Point;

typedef struct rect
{
    int xh, yh, xl, yl;
} Rect;

typedef struct rTreeNode
{
    int no_of_entries;
    int *hil_values;
    int max_hv;
    Rect rect;
    RTreeNode *child;
} RTreeNode;

typedef struct rTreeLeaf
{
    int no_of_entries;
    int *hil_values;
    int max_hv;
    Rect rect;
    Point *pt;
} RTreeLeaf;

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

int FindHilbertValue(Rect rectangle)
{
    int x_mid = (rectangle.xh + rectangle.xl) / 2;
    int y_mid = (rectangle.yh + rectangle.yl) / 2;

    int x_binary[8] = convertToBinary(x_mid);
    int y_binary[8] = convertToBinary(y_mid);

    int interleaf[16] = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);
}

void insert(RTreeNode root, Rect newRectangle)
{
}

int main()
{
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open file");
        exit(1);
    }

    char lines[21];
    char line[21];

    int x_coords[21];
    int y_coords[21];
    int num = 0;
    int x, y;
    while (fscanf(fp, "%d %d", &x, &y) == 2 && num <= 20)
    {
        x_coords[num] = x;
        y_coords[num] = y;
        num++;
    }
    fclose(fp);

    int min_x = x_coords[0], max_x = x_coords[0];
    int min_y = y_coords[0], max_y = y_coords[0];

    // Find the minimum and maximum x and y values in the set
    for (int i = 0; i <= num; i++)
    {
        if (x_coords[i] < min_x)
        {
            min_x = x_coords[i];
        }
        if (x_coords[i] > max_x)
        {
            max_x = x_coords[i];
        }
        if (y_coords[i] < min_y)
        {
            min_y = y_coords[i];
        }
        if (y_coords[i] > max_y)
        {
            max_y = y_coords[i];
        }
    }

    Rect mbr = {max_x, max_y, min_x, min_y};
}