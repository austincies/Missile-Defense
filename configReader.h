/*
 *@author: Austin Cieslinski
 *configReader.h
 */
#ifndef _CONFIGFILE_H
#define _CONFIGFILE_H

#include <stdio.h>

typedef struct configFile {
    char* defender;
    char* attacker;
    int missileCount;
    int *cityScape;
    int cityNum;
    int maxTower;
} Config;

/*
 *Reads a config file, checks for errors, then builds a config struct type
 *
 *FILE *fp: the config file
 *
 *returns: a config struct type
 */
Config *readConfig( FILE *fp );

#endif
