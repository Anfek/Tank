extern Tank* tank_going(Tank *tank, int dy, int dx);
extern Tank* turret_rotation(int previous_key, int current_key, Tank *tank);
extern int print_tank(Tank *tank);
extern void boom(void *data);

typedef struct {
    Data_Bullet bul;
    pthread_t thread;
    int count;
}Flag_thread;