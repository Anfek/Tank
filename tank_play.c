#include "tank.h"
#include "tank_bullet.h"
#include "tank_play.h"

static int *check_flag;

static void thread_flag(void *data){
    Flag_thread *flag = (Flag_thread*)data;
    pthread_join(flag->thread, NULL);
    pthread_mutex_lock(&mutex);
    check_flag[flag->count] = 0;
    pthread_mutex_unlock(&mutex);
}

void play(Tank *tank){   
    int ch, buf, previous_key = 0; 
    int check_pthread_create;
    pthread_t* parallel_bullet = (pthread_t*) malloc((NUMBER_OF_BULLETS)*sizeof(pthread_t));    //потоки пуль
    pthread_t* parallel_check = (pthread_t*) malloc((NUMBER_OF_BULLETS)*sizeof(pthread_t));     //потоки отслеживания потоков пуль

    Data_Bullet* bullet = (Data_Bullet*) malloc((NUMBER_OF_BULLETS)*sizeof(Data_Bullet));       //массив пуль
    Flag_thread* struct_thread_bullet = (Flag_thread*) malloc((NUMBER_OF_BULLETS)*sizeof(Flag_thread));       //массив отслеживания пуль

    check_flag = (int*) malloc((NUMBER_OF_BULLETS)*sizeof(int));                                //массив флагов отслеживания потоков пуль
    for (int i = 0; i < NUMBER_OF_BULLETS; i++){
        check_flag[i] == 0;
    }
    
    pthread_mutex_init(&mutex, NULL);
    int count = 0;  //для нумерации потоков
    while ((ch=getch())!=KEY_BACKSPACE && ch != 'r')
    {   
        switch (ch)
        {
        case 's':
            if(check_flag[count] != 0){
                int buf = count++;
                while (buf != count && check_flag[buf] == 1)
                    buf = (buf+1)%NUMBER_OF_BULLETS;
                if(buf == count)
                    break;
            }

            bullet[count].y = tank->tank[0][(int)tank->gun/3][(int)tank->gun%3];
            bullet[count].x = tank->tank[1][(int)tank->gun/3][(int)tank->gun%3];
            bullet[count].trajectory = tank->gun;

            check_pthread_create = pthread_create(&(parallel_bullet[count]), NULL, (void*)boom, (void*)&bullet[count]);
            if(check_pthread_create!=0){
                printf("Error create bullet\n");
                break;
            }
            struct_thread_bullet[count].bul = bullet[count];
            struct_thread_bullet[count].thread = parallel_bullet[count];
            struct_thread_bullet[count].count = count;

            check_pthread_create = pthread_create(&(parallel_check[count]), NULL, (void*)thread_flag, (void*)&struct_thread_bullet[count]);
            if(check_pthread_create!=0){
                printf("Error create thread check\n");
                break;
            }

            pthread_mutex_lock(&mutex);
            check_flag[count] = 1;
            pthread_mutex_unlock(&mutex);
            count=(count+1)%(NUMBER_OF_BULLETS);

            break;
        case 'q':
            tank->gun = UL;
            print_tank(tank);
            break;
        case 'w':
            tank->gun = U;
            print_tank(tank);            
            break;
        case 'e':
            tank->gun = UR;
            print_tank(tank); 
            break;
        case 'a':
            tank->gun = L;
            print_tank(tank); 
            break;
        case 'd':
            tank->gun = R;
            print_tank(tank); 
            break;
        case 'z':
            tank->gun = DL;
            print_tank(tank); 
            break;
        case 'x':
            tank->gun = D;
            print_tank(tank); 
            break;
        case 'c':
            tank->gun = DR;
            print_tank(tank); 
            break;
        case KEY_UP:
            if(tank->orient!=vertical) tank->orient=vertical;
            tank_going(tank, -1, 0);
            if(previous_key != 1){
                turret_rotation(previous_key, 1, tank);
                previous_key = 1;
            }
            print_tank(tank); 
            break;
        case KEY_DOWN:
            if(tank->orient!=vertical) tank->orient=vertical;
            tank_going(tank, 1, 0);
            if(previous_key != 3){
                turret_rotation(previous_key, 3, tank);
                previous_key = 3;
            }
            print_tank(tank); 
            break;
        case KEY_RIGHT:
            if(tank->orient!=horizontal) tank->orient=horizontal;
            tank_going(tank, 0, 1);
            if(previous_key != 2){
                turret_rotation(previous_key, 2, tank);
                previous_key = 2;
            }
            print_tank(tank); 
            break;
        case KEY_LEFT:
            if(tank->orient!=horizontal) tank->orient=horizontal;
            tank_going(tank, 0, -1);
            if(previous_key != 0){
                turret_rotation(previous_key, 0, tank);
                previous_key = 0;
            }
            print_tank(tank); 
            break;
        default:
            pthread_mutex_lock(&mutex);
            clear();
            pthread_mutex_unlock(&mutex);
            print_tank(tank);
        }      
    }
    pthread_mutex_destroy(&mutex);
}