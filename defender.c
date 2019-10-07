/*
 *@author: Austin Cieslinski
 *defender.c
 */
#include <pthread.h>
#include <curses.h>
#include <stdlib.h>
#include "defender.h"
#include "configReader.h"
#include "lock.h"
#include "attacker.h"

///Builds the defender
Defender *initDefender( Config *config, int height, int width ) {
    Defender *defender = malloc( sizeof( Defender ) );
    defender->pos = width/2;
    defender->height = height - ( config->maxTower + 2 );
    defender->width = width - 4;
    defender->graphic = "#####";
    return defender;
}

///Function used by the defender thread which allows the player to control
//the shield
void *runDefender( void *defend ) {
    Defender *def = (Defender *) defend;
    lock();
    mvaddstr( def->height, def->pos, def->graphic );
    unlock();
    int ch;
    while( 1 ) {
        ch = getch();
        if( ch == KEY_LEFT && def->pos - 1 > -1) {
            lock();
            move( def->height, def->pos );
            for( int i = 0; i < 5; i++ ) {
                delch();
            }
            mvaddstr( def->height, def->pos - 1, def->graphic );
            def->pos = def->pos - 1;
            refresh();
            unlock();
        }
        else if( ch == KEY_RIGHT && def->pos + 1 < def->width) {
            lock();
            move( def->height, def->pos );
            for( int i = 0; i < 5; i++ ) {
                delch();
            }
            mvaddstr( def->height, def->pos + 1, def->graphic );
            def->pos = def->pos + 1;
            refresh();
            unlock();
        }
        else if( ch == 'q' ) {
            quit();
            break;
        }
    }
    pthread_exit( NULL );
}
