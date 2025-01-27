#include "tank.h"

static void tank_clear(Tank *tank)
{
    for (int i = 0; i < 3; i++){
        for( int j = 0; j < 3; j++){
            pthread_mutex_lock(&mutex);
            mvaddch(tank->tank[0][i][j], tank->tank[1][i][j], ' ');
            pthread_mutex_unlock(&mutex);
        }
    }
}

Tank* tank_going(Tank *tank, int dy, int dx){
    tank_clear(tank);

    for (int i = 0; i < 3; i++){
        for( int j = 0; j < 3; j++){
            tank->tank[0][i][j]=(tank->tank[0][i][j] + dy + LINES)%LINES;
            tank->tank[1][i][j]=(tank->tank[1][i][j] + dx + COLS)%COLS;
        }
    }
    return tank;
}

static void special_transposition(int array[3][3]){ //как обычное транспонирование только начинаем снизу вверх в исходной матнице
    int new_array[3][3];
    for (int i = 0, j=2; i < 3; i++, j--)
        for (int k = 0; k < 3; k++)
            new_array[k][i] = array[j][k];
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            array[i][j] = new_array[i][j];
}

Tank* turret_rotation(int previous_key, int current_key, Tank *tank){
    int array [3][3] ={{0,0,0}, {0,0,0}, {0,0,0}};

    int row = (int)tank->gun/3; //строка матрицы
    int column = tank->gun%3;   //столбец матрицы
    array[row][column] = 1;

    while(previous_key!=current_key){
        special_transposition(array);
        previous_key = (previous_key+1)%4;
    }
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(array[i][j] == 1){
                tank->gun = i*3 + j;
                return tank;
            }
        }
    }
    return tank;
}
/*
000
100
000

010
000
000

000
001
000

000
000
010
*/