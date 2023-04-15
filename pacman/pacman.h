#ifndef _PACMAN_H_
#define _PACMAN_H_

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

int done();
void move(char direcao);

int isdirection(char direcao);
void ghosts();
void explode();
void explode2(int x, int y, int somax, int somay, int qtd);

#endif