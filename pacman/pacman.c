#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int haspower = 0;

int done()
{
    POSITION pos;

    int lost = !findmap(&m, &pos, HERO);
    int won = !findmap(&m, &pos, GHOST);

    return won || lost;
}

int isdirection(char direction)
{
    return direction == LEFT ||
           direction == UP ||
           direction == DOWN ||
           direction == RIGHT;
}

void move(char direction)
{

    int nextx = hero.x;
    int nexty = hero.y;

    switch (direction)
    {
    case LEFT:
        nexty--;
        break;
    case UP:
        nextx--;
        break;
    case DOWN:
        nextx++;
        break;
    case RIGHT:
        nexty++;
        break;
    }

    if (!canwalk(&m, HERO, nextx, nexty))
        return;

    if (ischaracter(&m, POWER, nextx, nexty))
    {
        haspower = 1;
    }

    walk(&m, hero.x, hero.y, nextx, nexty);
    hero.x = nextx;
    hero.y = nexty;
}

int ghostdestination(int currentx, int currenty,
                     int *finalx, int *finaly)
{

    int options[4][2] = {
        {currentx, currenty + 1},
        {currentx + 1, currenty},
        {currentx, currenty - 1},
        {currentx - 1, currenty}};

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int position = rand() % 4;

        if (canwalk(&m, GHOST, options[position][0], options[position][1]))
        {
            *finalx = options[position][0];
            *finaly = options[position][1];
            return 1;
        }
    }

    return 0;
}

void ghosts()
{
    MAP clonemap;

    copymap(&clonemap, &m);

    for (int i = 0; i < clonemap.lines; i++)
    {
        for (int j = 0; j < clonemap.columns; j++)
        {
            if (clonemap.matrix[i][j] == GHOST)
            {

                int finalx;
                int finaly;

                int found = ghostdestination(i, j, &finalx, &finaly);

                if (found)
                {
                    walk(&m, i, j, finalx, finaly);
                }
            }
        }
    }

    releasemap(&clonemap);
}

void explode2(int x, int y, int sumx, int sumy, int qt)
{

    if (qt == 0)
        return;

    int newx = x + sumx;
    int newy = y + sumy;

    if (!isvalid(&m, newx, newy))
        return;
    if (iswall(&m, newx, newy))
        return;

    m.matrix[newx][newy] = EMPTY;
    explode2(newx, newy, sumx, sumy, qt - 1);
}

void explode()
{
    if (!haspower)
        return;

    explode2(hero.x, hero.y, 0, 1, 3);
    explode2(hero.x, hero.y, 0, -1, 3);
    explode2(hero.x, hero.y, 1, 0, 3);
    explode2(hero.x, hero.y, -1, 0, 3);

    haspower = 0;
}

int main()
{

    readmap(&m);
    findmap(&m, &hero, HERO);

    do
    {
        printf("Power: %s\n", (haspower ? "YES" : "NO"));
        showmap(&m);

        char command;
        scanf(" %c", &command);

        if (isdirection(command))
            move(command);
        if (command == BOMB)
            explode();

        ghosts();

    } while (!done());

    releasemap(&m);
}