/*
 *@author: Austin Cieslinski
 *missile.h
 */
#ifndef _MISSILE_H
#define _MISSILE_H

typedef struct missile_struct {
    int height;
    int width;
    int yPos;
} Missile;

/*
 *Creates a missile struct type
 *
 *int height: the height of the terminal
 *
 *int width: the x-position of the missile
 */
Missile *initMissile( int height, int width );

/*
 *Runs the missile thread
 */
void *runMissile( void *missile );

#endif
