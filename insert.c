#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
#define M 4
#define m 2

int *convertToBinary(int number) //tested
{
    int* binary= (int*)malloc(8*sizeof(int));
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

int *createInterleaf(int x_binary[8], int y_binary[8]) //tested
{
    int* interleafBinary= (int*)malloc(16*sizeof(int));

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

int convertToDecimal(int *interleaf) //tested
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

    //malloc not needed?

    int *x_binary = convertToBinary(x_mid);
    int *y_binary = convertToBinary(y_mid);

    int *interleaf = createInterleaf(x_binary, y_binary);

    int hilbertValue = convertToDecimal(interleaf);

    rectangle.hilbertValue = hilbertValue;
}

void chooseLeaf(Rect rectangle)
{

}

void insert(RTreeNode root, Rect newRectangle)
{
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