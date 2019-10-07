/*
 *@author: Austin Cieslinski
 *missile.c
 */
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include "missile.h"
#include "lock.h"

///Creates a missile struct type
Missile *initMissile( int height, int width ) {
    Missile *missile = malloc( sizeof( Missile ) );
    missile->height = height;
    missile->yPos = 2;
    missile->width = width;
    return missile;
}

///Runs the missile thread
void *runMissile( void *miss ) {
    Missile *missile = (Missile *) miss;
    char below;
    srand( time( NULL ) );
    lock();
    move( missile->yPos, missile->width );
    addch( '|' );
    unlock();
    while( 1 ) {
        usleep( ( rand() % 400 ) * 1000 );
        lock();
	///When the missile will hit the ground
        if( missile->yPos + 1 == missile->height - 2 ) {
            move( missile->yPos + 1, missile->width );
            addch( '?' );
            move( missile->height - 1, missile->width );
            addch( '*' );
            move( missile->yPos, missile->width );
            addch( ' ' );
            refresh();
            unlock();
            break;
        }
        move( missile->yPos + 1, missile->width );
        below = inch();
	///When the missile will hit the sheild or a wall
        if( below == '#' || below == '|' ) {
            move( missile->yPos, missile->width );
            addch( '?' );
            move( missile->yPos + 1, missile->width );
            addch( '*' );
            refresh();
            unlock();
            break;
        }
	///When the missile will hit the top of a building or 
	//where a previous missile hit
        else if( below == '*' || below == '_' ) {
            move( missile->yPos + 1, missile->width );
            addch( '?' );
            move( missile->yPos + 2, missile->width );
            addch( '*' );
            move( missile->yPos, missile->width );
            addch( ' ' );
            refresh();
            unlock();
            break;
        }
        move( missile->yPos, missile->width );
        addch( ' ' );
        move( missile->yPos + 1, missile->width );
        addch( '|' );
        missile->yPos = missile->yPos + 1;
	    refresh();
        unlock();
    }
    pthread_exit( NULL );
}
