/*
 *attacker.h
 *@author: Austin Cieslinski
 */

#ifndef _ATTACKER_H
#define _ATTACKER_H
#include "configReader.h"

typedef struct attacker_struct {
    int height;
    int width;
    int missileCount;

} Attacker;
/*
 *The function the defender calls when the user presses the 'q' key.
 *Tells the attacker thread to quit early once a missile waves ends
 */
void quit();

/*
 *Builds an attacker struct using the config file and the 
 *height and width of the terminal
 *
 *Config config: the configuration file, the 
 *attacker uses it to determine the maximum number of missiles to spawn
 *
 *int height: the height of the terminal
 *
 *int width: the width of the terminal 
 *
 *returns: an attacker struct
 */
Attacker *initAttacker( Config *config, int height, int width );

/*
 *Runs the attacker thread, which creates threads of missiles
 *
 *void *attacker: the attacker struct which contains the terminal size and the
 *number of missiles to spawn
 */
void *runAttacker( void *attacker );

#endif
