/*
 *@author: Austin Cieslinski
 *threads.c
 */
#include <curses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "configReader.h"
#include "defender.h"
#include "attacker.h"
#include "lock.h"

/*
 *Builds the city using the config file and the dimensions of the terminal
 *
 *Config *config: the configuration file, contains the height of the buildings
 *
 *int height: the height of the terminal
 *
 *int width: the width of the terminal
 */
void initCity( Config *config, int height, int width ) {
    int ground = height - 2;
    int prev = ground;
    int this;
    int next;
    for( int i = 0; i < width; i++ ) {
        if( i >= config->cityNum ) {
            if( prev != ground ) {
                for( int j = ground; j >= prev; j-- ) {
                    move( j, i );
                    addch( '|' );
                }
            }
            else {
                move( ground, i );
                addch( '_' );
            }
            prev = ground;        
        }
        else {
            this = height - config->cityScape[i];
            if( i + 1 < config->cityNum  && i + 1 < width ) {
                next = height - config->cityScape[i + 1];
            }
            else {
                next = ground;
            }
            if( this == ground ) {
                move( ground, i );
                addch( '_' );
            }
            else if( this >= prev && this >= next ) {
                move( this - 1, i );
                addch( '_' );
            }
            else {
                for( int j = ground; j >= this; j-- ) {
                    move( j, i );
                    addch( '|' );
                }
            }
            prev = this;
        }
    }
    mvaddstr( 0, 4, "Enter 'q' to quit at end of attack, or control-c" );
}

/*
 *The main function of the game. Reads a config file, initializes the screen, 
 *spawns the attacker and defender, then waits for the threads to quit
 *
 *usage: threads config-file
 */
int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        fprintf( stderr, "Usage: threads config-file.\n" );
        exit( EXIT_FAILURE );
    }
    FILE *fp = fopen( argv[1], "r" );
    if( fp == NULL ) {
        fprintf( stderr, "Invalid config file.\n" );
        exit( EXIT_FAILURE );
    }
    Config *config = readConfig( fp );
    initscr();
    cbreak();
    keypad( stdscr, 1 );
    noecho();
    int width;
    int height;
    getmaxyx( stdscr, height, width );
    initCity( config, height, width );
    Defender *defender = initDefender( config, height, width );
    Attacker *attacker = initAttacker( config, height, width );
    pthread_t threads[2];
    void *retval;
    int rc;
    rc = pthread_create( &threads[1], NULL, runDefender, (void *) defender );
    if( rc ) {
        free( config->cityScape );
        free( config );
	free( defender );
        free( attacker );
        fprintf( stderr, "Error: pthread_create() returned %d\n", rc );
    }
    rc = pthread_create( &threads[0], NULL, runAttacker, (void *) attacker );
    if( rc ) {
        free( config->cityScape );
        free( config );
        free( defender );
        free( attacker );
        fprintf( stderr, "Error: pthread_create() returned %d\n", rc );
    }
    pthread_join( threads[0], &retval );
    mvprintw( 2, 4, "The %s attack has ended.", config->attacker );
    refresh();
    pthread_join( threads[1], &retval );
    mvprintw( 4, 4, "The %s defense has ended.", config->defender );
    free( config->cityScape );
    free( config->attacker );
    free( config->defender );
    free( config );
    free( defender );
    free( attacker );
    mvaddstr( 5, 4, "hit enter to close..." );
    getch();
    endwin();
    return 0;
}
