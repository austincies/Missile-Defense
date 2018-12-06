
typedef struct missile_struct {
    int height;
    int width;
    int yPos;
} Missile;

Missile *initMissile( int height, int width );

void *runMissile( void *missile );
