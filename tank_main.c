#include "tank.h"
#include "tank_main.h"


void hello(){
    clear();
    mvaddstr(LINES/3, COLS/3, "Hello!\n");
    mvaddstr(LINES/3+1, COLS/3, "Welcome to Tanchiki! The tank is controlled by arrows.");
    mvaddstr(LINES/3+2, COLS/3, "The position of the tower is controlled by the buttons around the 's' key. ");
    mvaddstr(LINES/3+3, COLS/3, "'s' - is responsible for the shot. Up to N shots are available to you at the same time.");
    mvaddstr(2*LINES/3, COLS/3, "Press any key to start playing...");
    getch();
    clear();
}

Tank create_tank(Tank *tank){
    tank->tank = (int ***)malloc(2 * sizeof(int**));
    for (int i = 0; i < 2; i++){
        tank->tank[i] = (int **)malloc(3 * sizeof(int*));
        for (int j = 0; j < 3; j++){
            tank->tank[i][j] = (int *)malloc(3 * sizeof(int));
        }        
    }

    tank->gun = L;
    tank->orient = horizontal;
    for (int i = 0; i <= 2; i++){
        for (int j = 0; j <= 2; j++){
            tank->tank[0][i][j]=LINES/2+i;  //y coord
            tank->tank[1][i][j]=COLS/2+j;   //x coord
        }
    }
    return *tank;
}


int	main(int argc, char *argv[])
{
    initscr();
    noecho();
    keypad (stdscr, TRUE);
    halfdelay(100);
    
    hello();

    Tank tank = create_tank(&tank);

    print_tank(&tank); 
    getch();
    play(&tank);
    
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++)
            free(tank.tank[i][j]);
        free(tank.tank[i]);
    }
    
    endwin();
    return 0;
}
