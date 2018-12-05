typedef struct defender_struct {
    int pos;
    int height;
    int width;
    char *graphic;
}Defender

Defender *initDefender( Config *config, int height, int width );

void *runDefender( void *defend );
