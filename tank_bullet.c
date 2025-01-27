#include "tank.h"
#include "tank_bullet.h"


void boom(void *data){
    Data_Bullet *bullet = (Data_Bullet*)data;

    int y, x, a, b, dx, dy;

    dy = (int)bullet->trajectory/3 - 1;
    dx = bullet->trajectory%3 - 1;
    y = bullet->y;
    x = bullet->x;
    a=y+dy;
    b=x+dx;
    while (y>0 && x>0 && y<LINES && x<COLS)
    {
        //buf_check(data->tank_y, data->tank_x, data->buf);
        mvaddch(a, b, ' ');

        y+=dy; 
        x+=dx; 

        mvaddch(y, x, 'o');
        refresh();
        usleep(500000);
        a=y; b=x;
    }
    mvaddch(a, b, ' ');
    refresh();
    pthread_exit(0);
}