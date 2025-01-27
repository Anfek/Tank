#include "tank.h"

static int print_gun(Tank *tank){
    char ch;
    int x, y;
    if(tank->gun == UL || tank->gun == DR)
        ch = '\\';
    else if(tank->gun == UR || tank->gun == DL)
        ch = '/';
    else if(tank->gun == R || tank->gun == L)
        ch = '-';
    else if(tank->gun == U || tank->gun == D)
        ch = '|';
    
    x = (int)tank->gun/3;
    y = tank->gun%3;
    
    pthread_mutex_lock(&mutex);
    mvaddch(tank->tank[0][x][y], tank->tank[1][x][y], ch);
    refresh();
    pthread_mutex_unlock(&mutex);
    return 1;
}

static int print_tank_vertical(Tank *tank){
    //clear();
    pthread_mutex_lock(&mutex);
    mvaddch(tank->tank[0][0][1], tank->tank[1][0][1], ' ');
    mvaddch(tank->tank[0][2][1], tank->tank[1][2][1], ' ');
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if(j==0 || j==2 || i==j==1){
                pthread_mutex_lock(&mutex);
                mvaddch(tank->tank[0][i][j], tank->tank[1][i][j], '*');
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    print_gun(tank);
    
    refresh();
    return 1;
}

static int print_tank_horizontally(Tank *tank){
    //clear();
    pthread_mutex_lock(&mutex);
    mvaddch(tank->tank[0][1][0], tank->tank[1][1][0], ' ');
    mvaddch(tank->tank[0][1][2], tank->tank[1][1][2], ' ');
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if(i==0 || i==2 || i==j==1){
                pthread_mutex_lock(&mutex);
                mvaddch(tank->tank[0][i][j], tank->tank[1][i][j], '*');
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    print_gun(tank);
    
    refresh();
    return 1;
}

int print_tank(Tank *tank){
    int res = tank->orient == vertical ? print_tank_vertical(tank) : print_tank_horizontally(tank);

    return res;
}