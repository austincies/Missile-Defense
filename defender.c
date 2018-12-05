#include <pthreads.h>
#include <stdlib.h>
#include "defender.h"
#include "configReader.h"
#include "lock.h"

Defender *initDefender( Config *config, int height, int width ) {
    Defender *defender;
    defender->pos = width/2;
    defender->height = height - ( config->maxTower + 2 );
    defender->width = width - 4;
    defender->graphic = "#####";
    return defender;
}

void *runDefender( void *defend ) {
    Defender *def = (Defender *) defend;
    lock();
    mvaddrstr( def->height, def->pos, def->graphic );
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
            mvaddrstr( def->height, def->pos - 1, def->graphic );
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
            mvaddrstr( def->height, def->pos + 1, def->graphic );
            def->pos = def->pos + 1;
            refresh();
            unlock();
        }
        else if( ch == 'q' ) {
            break;
        }
    }
    pthread_exit( NULL );
}
