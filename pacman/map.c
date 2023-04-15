#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <string.h>

void readmap(MAP *m)
{
    FILE *f;
    f = fopen("map.txt", "r");
    if (f == 0)
    {
        printf("Error reading map");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->lines), &(m->columns));
    allocmap(m);

    for (int i = 0; i < m->lines; i++)
    {
        fscanf(f, "%s", m->matrix[i]);
    }

    fclose(f);
}

void allocmap(MAP *m)
{
    m->matrix = malloc(sizeof(char *) * m->lines);

    for (int i = 0; i < m->lines; i++)
    {
        m->matrix[i] = malloc(sizeof(char) * m->columns + 1);
    }
}

void copymap(MAP *destination, MAP *source)
{
    destination->lines = source->lines;
    destination->columns = source->columns;
    allocmap(destination);
    for (int i = 0; i < source->lines; i++)
    {
        strcpy(destination->matrix[i], source->matrix[i]);
    }
}

void releasemap(MAP *m)
{
    for (int i = 0; i < m->lines; i++)
    {
        free(m->matrix[i]);
    }

    free(m->matrix);
}

int findmap(MAP *m, POSITION *p, char c)
{

    for (int i = 0; i < m->lines; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            if (m->matrix[i][j] == c)
            {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }

    return 0;
}

int canwalk(MAP *m, char character, int x, int y)
{
    return isvalid(m, x, y) &&
           !iswall(m, x, y) &&
           !ischaracter(m, character, x, y);
}

int isvalid(MAP *m, int x, int y)
{
    if (x >= m->lines)
        return 0;
    if (y >= m->columns)
        return 0;

    return 1;
}

int ischaracter(MAP *m, char character, int x, int y)
{
    return m->matrix[x][y] == character;
}

int iswall(MAP *m, int x, int y)
{
    return m->matrix[x][y] == VERTICAL_WALL ||
           m->matrix[x][y] == HORIZONTAL_WALL;
}

void walk(MAP *m, int sourcex, int sourcey,
          int destinationx, int destinationy)
{

    char character = m->matrix[sourcex][sourcey];
    m->matrix[destinationx][destinationy] = character;
    m->matrix[sourcex][sourcey] = EMPTY;
}