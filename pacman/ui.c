#include <stdio.h>
#include "map.h"

char drawwall[4][7] = {
    {"......"},
    {"......"},
    {"......"},
    {"......"}};

char drawghost[4][7] = {
    {" .-.  "},
    {"| OO| "},
    {"|   | "},
    {"'^^^' "}};

char drawhero[4][7] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\  '-."},
    {" '--' "}};

char drawpower[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}};

char emptyspot[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}};

void partialshow(char img[4][7], int partial)
{
    printf("%s", img[partial]);
}

void showmap(MAP *m)
{
    for (int i = 0; i < m->lines; i++)
    {

        for (int partial = 0; partial < 4; partial++)
        {
            for (int j = 0; j < m->columns; j++)
            {

                switch (m->matrix[i][j])
                {
                case GHOST:
                    partialshow(drawghost, partial);
                    break;
                case HERO:
                    partialshow(drawhero, partial);
                    break;
                case POWER:
                    partialshow(drawpower, partial);
                    break;
                case VERTICAL_WALL:
                case HORIZONTAL_WALL:
                    partialshow(drawwall, partial);
                    break;
                case EMPTY:
                    partialshow(emptyspot, partial);
                    break;
                }
            }
            printf("\n");
        }
    }
}