#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rtree.h"
#define M 4
#define m 2


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
