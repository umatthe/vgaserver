
/*
//////////////////////////////////////////////////////////////////////////////
//
//               S O K O B A N
//
//
//  FILE:        main.c
//
//  PURPOSE:     sokoban
//
//
//               Copyright (c) 2006 M. Bruestle, Vienna (AT)
//
//  Andre Saischowa AWT800-Port / 2024
//
//////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <stdlib.h>
#include <iocntrl.h>
#include <process.h>

#define AS_ATW800 1

#ifdef AS_ATW800

    #define ATARI_HOST 1 /*important for atw800/2*/

    #define ATARI_1024 1 /* define for 1440 resolution */

    #define ATARI_1440 1 /* define for 1440 resolution */
    /*#undef ATARI_1440     uncomment for 1280 resolution */

    #ifdef ATARI_HOST
        /* with ATW800/2-Splitscreen 1440x800 (640x800 + 800x800)
        VTG is setting from Atari
        */

       #ifdef ATARI_1024

          #define AS_AWT_SCREEN_VRAM  (0x80600000 + 384)
          #define AS_AWT_SCREEN_STRIDE      1024

          #define AS_AWT_SCREEN_WIDTH       640
          #define AS_AWT_SCREEN_HEIGHT      480
          #define AS_AWT_SCREEN_COLORDEPTH   8

       #elif ATARI_1440
          #define AS_AWT_SCREEN_VRAM  (0x80600000 +640)
          #define AS_AWT_SCREEN_STRIDE      1440

          #define AS_AWT_SCREEN_WIDTH       800
          #define AS_AWT_SCREEN_HEIGHT      800
          #define AS_AWT_SCREEN_COLORDEPTH   8

       #else /* Spittscreen 1280x800 (640x800 + 640x800) */
          #define AS_AWT_SCREEN_VRAM  (0x80600000 +640)
          #define AS_AWT_SCREEN_STRIDE      1280

          #define AS_AWT_SCREEN_WIDTH       640
          #define AS_AWT_SCREEN_HEIGHT      800
          #define AS_AWT_SCREEN_COLORDEPTH   8

    #endif

    #else
        /* Standalone - Version , VTG is setting, not for ATW800/2 !!!*/
        #define AS_AWT_SCREEN_VRAM  0x80600000
        #define AS_AWT_SCREEN_STRIDE      800

        #define AS_AWT_SCREEN_WIDTH       800
        #define AS_AWT_SCREEN_HEIGHT      600
        #define AS_AWT_SCREEN_COLORDEPTH   8

        #define AWT_INIT_VTG 1

    #endif

    #define AWT_GFX_IMPLEMENTATION
    #include "..\dev-deps\awt_gfx.h"


#else
    /* Graphic over iserver with vram / M. Bruestle */
    #include "vram.h"

#endif

#include "sokoban.h"

#define XPIC   20
#define YPIC   20

#define XRES (40*XPIC)
#define YRES (24*YPIC)

#define XOFF 10
#define YOFF  6

/* direction = bit 0 */
/* row/col   = bit 1 */

#define _E_ 0
#define _W_ 1
#define _S_ 2
#define _N_ 3

long int palette[] = { 0x00000080
                     , 0x0000FFFF
                     };

extern char *_GamePic;


/*-----------------------------------------------------------------------------------------------*/
static unsigned int Draw( int id, int dir, int x, int y, int n, char *c ) {
/*-----------------------------------------------------------------------------------------------*/

    x *= XPIC;
    y *= YPIC;

    for (;;) {

       uint8_t *srcAdr  =(uint8_t*)( _GamePic + ( *c * ( XPIC * YPIC )) );
       awtBlitRect(x,y,XPIC,YPIC,srcAdr,XPIC);

        if ( n == 1 ) break;

        n--;

        if ( dir & 1 ) {
            c--;
        } else {
            c++;
        } /* endif */

        if ( dir & 2 ) {
            y += YPIC;
        } else {
            x += XPIC;
        } /* endif */

    } /* endfor */

    return 0;
}

/*-----------------------------------------------------------------------------------------------*/
static unsigned int Redraw( int id, SOKOSTATE *s, int i ) {
/*-----------------------------------------------------------------------------------------------*/

    int x = 0, y = 0;
    char c;

    (void)i;

    for (;;) {
        if (( c = Get1Soko( s, x, y )) == 0xFF ) {
            if ( x == 0 ) break;
            y++; x = 0;
        } else {
            Draw( id, _N_, x + XOFF, y + YOFF, 1, &c );
            x++;
        } /* endif */
    } /* endfor */

    return 0;
}

/*===============================================================================================*/
int main( int argc, char *argv[] ) {
/*===============================================================================================*/

    int id, i = 0, x, y;
    SOKOSTATE state;
    FILE *f = NULL;


#ifndef AS_ATW800
    if ( argc < 2 || argc > 3 ) {
        return 1;
    } else if (( id = VramCreate( argv[ 1 ], XRES, YRES, 8, 1 )) > 0 ) {
        printf( "created: %d\n", id );
    } else if (( id = VramOpen( argv[ 1 ] )) > 0 ) {
        printf( "opened: %d\n", id );
    } else {
        return 2;
    } /* endif */
#endif
    /*if ( argc == 3 ) f = fopen( argv[ 2 ], "r" );*/

   f = fopen( "VALIDATE", "r" );

    awtSetPaletteColor(0,   0,    0, 0x80);
    awtSetPaletteColor(' ', 0,    0, 0x80);
    awtSetPaletteColor('#', 0, 0xFF, 0xFF);
    awtInitVTG();

restart:

    printf( "i=%d\n", i );

    awtClearScreen();

    InitSoko( &state, i, &x, &y );


    x += XOFF;
    y += YOFF;

    Redraw( id, &state, i );

    for (;;) {

        int pre = 0, key;
        char out[ 3 ], c;

        if ( f != NULL ) {
           key = getc( f );
           if ( key == EOF ) break;
           if ( key == '\n' ) continue;
           ProcWait( 1000 );
        } else {
           while (( key = pollkey()) == -1 );
        } /* endif */

        if (( c = (char)key ) == 'q' ) {
            break;
        } /* endif */

        switch ( key ) {
            case 'N':
            case 72: c = 'n'; break;
            case 'S':
            case 80: c = 's'; break;
            case 'W':
            case 75: c = 'w'; break;
            case 'E':
            case 77: c = 'e'; break;
        }

        switch ( c ) {
            case 'u': c = UndoSoko( &state, out    ); pre = -1; break;
            case 'r': c = RedoSoko( &state, out    ); pre =  0; break;
            case 'n':
            case 's':
            case 'w':
            case 'e': c = MoveSoko( &state, out, c ); pre =  0; break;
            case 'i': ExitSoko( &state );                   ; goto restart; break;
            case 'o': ExitSoko( &state ); if ( i >   0 ) i--; goto restart; break;
            case 'p': ExitSoko( &state ); if ( i < 103 ) i++; goto restart; break;
            default : continue;
        } /* endswitch */

        switch ( c ) {
            case 'n': y -= pre; Draw( id, _N_, x    , y - 1, 2, out + 1 ); y -= 1 + pre; break;
            case 'N': y -= pre; Draw( id, _N_, x    , y - 2, 3, out + 2 ); y -= 1 + pre; break;
            case 's': y += pre; Draw( id, _S_, x    , y    , 2, out     ); y += 1 + pre; break;
            case 'S': y += pre; Draw( id, _S_, x    , y    , 3, out     ); y += 1 + pre; break;
            case 'w': x -= pre; Draw( id, _W_, x - 1, y    , 2, out + 1 ); x -= 1 + pre; break;
            case 'W': x -= pre; Draw( id, _W_, x - 2, y    , 3, out + 2 ); x -= 1 + pre; break;
            case 'e': x += pre; Draw( id, _E_, x    , y    , 2, out     ); x += 1 + pre; break;
            case 'E': x += pre; Draw( id, _E_, x    , y    , 3, out     ); x += 1 + pre; break;
        } /* endswitch */

        if ( state.CntHome == 0 ) {
            if ( i == 103 ) break;
            ExitSoko( &state ); i++; goto restart;
        } /* endif */

    } /* endfor */
    awtClose();
    return 0;
}
