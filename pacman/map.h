#ifndef _MAP_H_
#define _MAP_H_

#define HERO '@'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define GHOST 'F'
#define POWER 'P'

struct map
{
    char **matrix;
    int lines;
    int columns;
};

typedef struct map MAP;

void allocmap(MAP *m);
void readmap(MAP *m);
void releasemap(MAP *m);

struct position
{
    int x;
    int y;
};

typedef struct position POSITION;

int findmap(MAP *m, POSITION *p, char c);

int isvalid(MAP *m, int x, int y);
int iswall(MAP *m, int x, int y);
int ischaracter(MAP *m, char character, int x, int y);

void walk(MAP *m, int sourcex, int sourcey,
          int destinationx, int destinationy);

void copymap(MAP *destination, MAP *source);

int canwalk(MAP *m, char character, int x, int y);

#endif