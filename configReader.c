/*
 *@author: Austin Cieslinski
 *configReader.c
 */
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "configReader.h"

///Reads a config file, checks for errors, then builds a config struct type
Config *readConfig( FILE *fp ) {
    Config *config = malloc( sizeof( Config ) );
    int lineCount = 0;
    size_t bufSize = 0;
    char *buf = NULL;
    char *defender = malloc( sizeof( char ) * 80 );
    char *attacker = malloc( sizeof( char ) * 80 );
    int missiles;
    int citySize = 1;
    int cityNum = 0;
    int *cityScape = malloc( citySize * sizeof( int ) );
    int maxTower = 0;
    while( getline( &buf, &bufSize, fp ) > 0 ) {
        if( buf[0] != '#' ) {
            int x = strlen( buf );
            if( buf[x - 1] == '\n' ) {
                buf[x - 1] = '\0';
            }
            //check for defender name
            if( lineCount == 0 ) {
                if( strlen( buf ) > 80 || strlen( buf ) == 0) {
                    fprintf( stderr, "Invalid defender name size: "
                            "must be under 80 characters or above 0.\n" );
                    fclose( fp );
                    free( cityScape );
                    free( config );
                    exit( EXIT_FAILURE );
                }
                sscanf( buf, "%[^\n]", defender );
                lineCount = lineCount + 1;
            }
            //check for attacker name
            else if( lineCount == 1 ) {
                if( strlen( buf ) > 80 || strlen( buf ) == 0 ) {
                    fprintf( stderr, "Invalid attacker name size: "
                            "must be under 80 characters or above 0.\n" );
                    fclose( fp );
                    free( cityScape );
                    free( config );
                    exit( EXIT_FAILURE );
                }
                sscanf( buf, "%[^\n]", attacker );
                lineCount = lineCount + 1;
            }
            //check for missile count
            else if( lineCount == 2 ) {
                for( int i = 0; i < (int) strlen( buf ); i++ ) {
                    if( !isdigit( buf[i] ) ) {
                        fprintf( stderr, "Invalid missile count: "
                                "not an integer.\n" );
                        fclose( fp );
                        free( cityScape );
                        free( config );
                        exit( EXIT_FAILURE );
                    }
                }
                sscanf( buf, "%d", &missiles );
                if( missiles < 0 ) {
                    fprintf( stderr, "Invalid missile count: "
                            "missile count must be 0 or higher\n" );
                    fclose( fp );
                    free( cityScape );
                    free( config );
                    exit( EXIT_FAILURE );
                }
                lineCount = lineCount + 1;
            }
            //read lines to build cityscape
            else if( lineCount > 2 ) {
                char *tok = strtok( buf, " " );
                while( tok != NULL ) { 
                    if( cityNum >= citySize ) {
                        citySize = citySize + 1;
                        int *tmp = realloc( cityScape, citySize 
                                * sizeof( int ) );
                        cityScape = tmp;
                    }
                    for( int i = 0; i < (int) strlen( tok ); i++ ) {
                        if( !isdigit( tok[i] ) ) {
                            fprintf( stderr, "Invalid city layout: "
                                    "not an integer.\n" );
                            fclose( fp );
                            free( cityScape );
                            free( config );
                            exit( EXIT_FAILURE );
                        }
                    }
                    int size;
                    sscanf( tok, "%d", &size );
                    if( size < 2 ) {
                        fprintf( stderr, "Invalid city layout: "
                                "must be 2 or greater.\n" );
                        fclose( fp );
                        free( cityScape );
                        free( config );
                        exit( EXIT_FAILURE );
                    }
                    if( size > maxTower ) {
                        maxTower = size;
                    }
                    cityScape[cityNum] = size;
                    cityNum = cityNum + 1;
                    tok = strtok( NULL, " " );
                }
                lineCount = lineCount + 1;
            }
        }
    }
    if( lineCount == 0 ) {
        fprintf( stderr, "Error: missing defender name.\n" );
        fclose( fp );
        free( cityScape );
        free( config );
        exit( EXIT_FAILURE );
    }
    else if( lineCount == 1 ) {
        fprintf( stderr, "Error: missing attacker name.\n" );
        fclose( fp );
        free( cityScape );
        free( config );
        exit( EXIT_FAILURE );
    }
    else if( lineCount == 2 ) {
        fprintf( stderr, "Error: missing missile count.\n" );
        fclose( fp );
        free( cityScape );
        free( config );
        exit( EXIT_FAILURE );
    }
    else if( lineCount < 4 ) {
        fprintf( stderr, "Invalid configuration file size\n" );
        fclose( fp );
        free( cityScape );
        free( config );
        exit( EXIT_FAILURE );
    }
    config->defender = defender;
    config->attacker = attacker;
    config->missileCount = missiles;
    config->cityScape = cityScape;
    config->cityNum = cityNum;
    config->maxTower = maxTower;
    return config;
}

