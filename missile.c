#define _DEFAULT_SOURCE

#include <pthread.>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include "missile.h"
#include "lock.h"

Missile *initMissile( int height, int width ) {
    Missile missile;
    missile->height = height;
    missile->yPos = 2;
    missile->width = width;
    return missile;
}

void *runMissile( void *missile ) {
    char below;
    srand( time( NULL ) );
    lock();
    move( missile->yPos, missile->width );
    addch( '|' );
    unlock();
    while( 1 ) {
        usleep( ( rand() % 200 ) * 1000 );
        lock();
        if( missile->yPos + 1 == missile->height - 2 ) {
            move( missile->yPos, missile->width );
            addch( '?' );
            move( missile->height - 1, missile->width );
            addch( '*' );
            refresh();
            unlock();
            break;
        }
        move( missile->yPos + 1, missile->width );
        below = inch();
        if( below == '#' || below == '*' || below == '|' ) {
            move( missile->yPos, missile->width );
            addch( '?' );
            move( missile->yPos + 1, missile->width );
            addch( '*' );
            refresh();
            unlock();
            break;
        }
        else if( below == '_' ) {
            move( missile->yPos + 1, missile->width );
            addch( '?' );
            move( missile->yPos + 2, missile->width );
            addch( '*' );
            refresh();
            unlock();
            break;
        }
        move( missile->yPos, missile->width );
        addch( ' ' );
        move( missile->yPos + 1, missile->width );
        addch( '|' );
        missile->yPos = missile->yPos + 1;
        unlock();
    }
    pthread_exit( NULL );
}
