
typedef struct attacker_struct {
    int height;
    int width;
    int missileCount;

} Attacker;

Attacker *initAttacker( int height, int width, Config *config );

void *runAttacker( void *attacker );
