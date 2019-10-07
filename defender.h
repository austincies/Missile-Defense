/*
 *@author: Austin Cieslinski
 *defender.h
 */
#ifndef _DEFENDER_H
#define _DEFENDER_H

#include "configReader.h"

typedef struct defender_struct {
    int pos;
    int height;
    int width;
    char *graphic;
}Defender;

/*
 *Builds the defender using the config file 
 *and the height and width of the terminal
 *
 *Config *config: the config file that is used to 
 *determine the height of the defender
 *
 *int height: the height of the terminal
 *
 *int width: the width of the terminal
 */
Defender *initDefender( Config *config, int height, int width );

/*
 *Function used by the defender thread.
 *The player can use the left and right arrow keys to move the shield or
 *press 'q' to quit the game
 */
void *runDefender( void *defend );

#endif
