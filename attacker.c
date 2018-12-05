#include <pthreads.h>
#include "attacker.h"
#include "configReader.h"
#include "missile.h"

#define WAVE_SIZE 10

Attacker *initAttacker( int height, int width, Config *config ) {
    Attacker *attacker;
    attacker->height = height;
    attacker->width = width;
    attacker->missileCount = config->missileCount;
    return attacker;
}

void *runAttacker( void *attacker ) {
    Attacker *att = (Attacker *) attacker;
    int missileCount;
    if( att->missileCount == 0 ) {
        missileCount = -1;
    }
    else {
        missileCount = attacker->missileCount
    }
    Missile **missiles = malloc( sizeof( Missile *) * WAVE_SIZE );
    int numMissiles = WAVE_SIZE;
    pthread_t threads[WAVE_SIZE];
    void *retval;
    while( missileCount > 0 || missileCount == -1 ) {
        if( missileCount < WAVE_SIZE && missileCount != -1 ) {
            numMissiles = missileCount;
            missileCount = 0;
        }
        for( int i = 0; i < numMissiles; i++ ) {
            Missile *newMissile = initMissile( att->height, att->width);
            missiles[i] = newMissile;
        }
        for( int i = 0; i < numMissiles; i++ ) {
            pthread_create( &threads[i], NULL, 
                    runMissile, (void *)missiles[i] );
        }
        for( int i = 0; i < numMissiles; i++ ) {
            pthread_join( threads[i], &retval );
        }
    }
    pthread_exit( NULL );
}
