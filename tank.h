#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    UL = 0, U = 1, UR = 2, 
    L = 3,          R = 5, 
    DL = 6, D = 7, DR = 8
} Gun;  //местоположение башни верхнее левое, верхнее, ...

typedef enum {vertical, horizontal} Orientation;

typedef struct
{
    int ***tank;    //tank[2][3][3] : tank[координаты y, x][номер символа в танке по горизонтали][-//- по вертикали]
    Gun gun;    // положение пушки
    Orientation orient; //ориентация танка
}Tank;

static pthread_mutex_t mutex;
