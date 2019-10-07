/*
 *@author: Austin Cieslinski
 *attacker.c
 */
#define _DEFAULT_SOURCE

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "attacker.h"
#include "configReader.h"
#include "missile.h"

#define WAVE_SIZE ( ( att->width / 10 ) + 1 )

int quitA = 0;

///Tells the attacker thread to quit early once a missile waves ends
void quit() {
    quitA = 1;
}

///Builds an attcker struct using the config file and the
///height and width of the terminal
Attacker *initAttacker( Config *config, int height, int width ) {
    Attacker *attacker = malloc( sizeof( Attacker ) );
    attacker->height = height;
    attacker->width = width;
    attacker->missileCount = config->missileCount;
    return attacker;
}

///Runs the attacker thread, which creates threads of missiles
void *runAttacker( void *attacker ) {
    Attacker *att = (Attacker *) attacker;
    int missileCount;
    if( att->missileCount == 0 ) {
        missileCount = -1;
    }
    else {
        missileCount = att->missileCount;
    }
    Missile **missiles = malloc( sizeof( Missile *) * WAVE_SIZE );
    int numMissiles = WAVE_SIZE;
    pthread_t threads[WAVE_SIZE];
    srand( time( NULL ) );
    void *retval;
    while( missileCount > 0 || missileCount == -1 ) {
        usleep( 1000 );
        if( missileCount < WAVE_SIZE && missileCount != -1 ) {
            numMissiles = missileCount;
            missileCount = 0;
        }
        else {
            missileCount = missileCount - numMissiles;
        }
        for( int i = 0; i < numMissiles; i++ ) {
            Missile *newMissile = initMissile( att->height, rand() 
                    % att->width );
            missiles[i] = newMissile;
        }
        for( int i = 0; i < numMissiles; i++ ) {
            usleep( rand() % 500 );
            pthread_create( &threads[i], NULL, 
                    runMissile, (void *)missiles[i] );
        }
        for( int i = 0; i < numMissiles; i++ ) {
            pthread_join( threads[i], &retval );
            free( missiles[i] );
        }
        if( quitA ) {
            break;
        }
    }
    free( missiles );
    pthread_exit( NULL );
}
