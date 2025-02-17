/*
/////////////////////////////////////////////////////////////////////////////////////////////
//
//               S O K O B A N
//
//
//  FILE:        sokoban.c
//
//  PURPOSE:     the real sokoban code
//
//
//               Copyright (c) 2006 M. Bruestle, Vienna (AT)
//
/////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <string.h>
#include <stdlib.h>
#include "sokoban.h"

extern char *_GameDef[];

#define MOVE_RECORDER_BLOCK_SIZE 512
#define NUL '\0'

/*=========================================================================================*/
char MoveSoko( SOKOSTATE *State, char *c, char Direction ) {
/*=========================================================================================*/

    char *p, c0, c1, c2, result = NUL;
    int Move;

    /* --- convert a direction into a movedistance (2 dimension to 1 dimension) ---------- */

    switch ( Direction ) {
        case 'n'  : Move = -State->SizeX; break;
        case 's'  : Move = +State->SizeX; break;
        case 'w'  : Move = -1;            break;
        case 'e'  : Move = +1;            break;
        default   : return NUL; /* why me ... */
    } /* endswitch */

    /* --- we have a movedistance. get the fieldvalue where sokoban try to move ---------- */

    p  = State->Field + State->PosSoko;
    c0 = *p;                                     /* c0 = soko old                          */
    p += Move;                                   /* p now points to sokos destinationfield */
    c1 = *p;                                     /* c1 = soko new                          */

    /* --- if moverecorder is full, extend it -------------------------------------------- */

    if ( State->CntMove >= State->SizeMove ) {
        State->SizeMove += MOVE_RECORDER_BLOCK_SIZE;
        State->Moves = realloc( State->Moves, State->SizeMove );
        memset( State->Moves + ( State->SizeMove - MOVE_RECORDER_BLOCK_SIZE )
              , 0
              , MOVE_RECORDER_BLOCK_SIZE );
    } /* endif */

    /* --- check the fieldvalues without the HOMEBIT ------------------------------------- */

    if (( c1 & ~HOMEBIT ) == EMPTY ) {

        /* --- it is a legal move (no push), update sokobans position -------------------- */

        State->PosSoko += Move;

        /* --- record move (=save direction) and movecounter ----------------------------- */

        State->Moves[ State->CntMove++ ] = Direction;

        /* --- we move from empty to empty, nothing to update in the field --------------- */

        ;

        /* --- fill changebuffer (with soko) --------------------------------------------- */

        c[ 0 ] =   c0;
        c[ 1 ] = ( c1 & HOMEBIT ) | SKBAN;

        /* --- return movedirection and sizeindikator (lowercase = 2) -------------------- */

        result = Direction;

    } else if ((( c1 & ~HOMEBIT ) == BRICK )
           && ((( c2 = *( p + Move )) & ~HOMEBIT ) == EMPTY )) {

        /* --- it is a legal push, update sokobans position ------------------------------ */

        State->PosSoko += Move;

        /* --- record push (=save uppercase direction), pushcounter and movecounter ------ */

        State->Moves[ State->CntMove++ ] = Direction & ~0x20; /* toupper 4 "nswe" */
        State->CntPush++;

        /* --- we push one brick, update fields (preserve HOMEBITs) ---------------------- */

        *( p        ) = ( c1 & HOMEBIT ) | EMPTY;
        *( p + Move ) = ( c2 & HOMEBIT ) | BRICK;

        /* --- fill changebuffer (with soko) --------------------------------------------- */

        c[ 0 ] =   c0;
        c[ 1 ] = ( c1 & HOMEBIT ) | SKBAN;
        c[ 2 ] = ( c2 & HOMEBIT ) | BRICK;

        /* --- brick move from 1 to 2, so update homecounter ----------------------------- */
        
        State->CntHome += ( (int)c1 & HOMEBIT ) - ( (int)c2 & HOMEBIT );

        /* --- return movedirection and sizeindikator (uppercase = 3) -------------------- */

        result = Direction & ~0x20;

    } else {

        /* --- we hit a wall or try to push too hard ------------------------------------- */

    } /* endif */

    return result;
}

/*=========================================================================================*/
char RedoSoko( SOKOSTATE *State, char *c ) {
/*=========================================================================================*/

    if ( State->Moves[ State->CntMove ] == NUL ) return 0;

    return MoveSoko( State, c, State->Moves[ State->CntMove ] | 0x20 );  /* tolower 4 "nswe" */
}

/*=========================================================================================*/
char UndoSoko( SOKOSTATE *State, char *c ) {
/*=========================================================================================*/

    /*
     * undo of a move is a simple positionupdate in the opposite direction and a decrement
     * of the movecounter. all undooperations must succeed, because they where recorded
     * by legal moves and pushs by MoveSoko().
     *
     */

    char *p, c0, c1, c2, Direction;
    int Move;

    /* --- check if we have recorded moves ----------------------------------------------- */

    if ( State->CntMove <= 0 ) return NUL;

    /* --- get previos move from recordbuffer -------------------------------------------- */

    State->CntMove--;
    Direction = State->Moves[ State->CntMove ];

    /* --- convert a direction into a reverse movedistance (undo) ------------------------ */

    switch ( Direction | 0x20 ) {
        case 'n'  : Move = +State->SizeX; break;
        case 's'  : Move = -State->SizeX; break;
        case 'w'  : Move = +1;            break;
        case 'e'  : Move = -1;            break;
        default   : return NUL; /* why me ... */
    } /* endswitch */

    /* --- we have a movedistance. get the fieldvalue where sokoban step back ------------ */

    p  = State->Field + State->PosSoko;
    c0 = *( p + Move );
    c1 = *( p        );

    /* --- update sokobans position ------------------------------------------------------ */

    State->PosSoko += Move;

    /* --- was it a move or a push ? ----------------------------------------------------- */

    if ( Direction & 0x20 ) {

        /* --- move -> back ( nothing to update in the field ) --------------------------- */

        ;

        /* --- fill changebuffer (with soko) --------------------------------------------- */

        c[ 0 ] = ( c0 & HOMEBIT ) | SKBAN;
        c[ 1 ] =   c1;

    } else {

        /* --- push -> pull -------------------------------------------------------------- */

        State->CntPush--;

        c2 = *( p - Move );

        /* --- update field (preserve HOMEBITs) ------------------------------------------ */

        *( p        ) = ( c1 & HOMEBIT ) | BRICK;
        *( p - Move ) = ( c2 & HOMEBIT ) | EMPTY;

        /* --- fill changebuffer (with soko) --------------------------------------------- */

        c[ 0 ] = ( c0 & HOMEBIT ) | SKBAN;
        c[ 1 ] = ( c1 & HOMEBIT ) | BRICK;
        c[ 2 ] = ( c2 & HOMEBIT ) | EMPTY;

        /* --- brick move from 2 to 1, so update homecounter ----------------------------- */
        
        State->CntHome += ( (int)c2 & HOMEBIT ) - ( (int)c1 & HOMEBIT );

    } /* endif */

    return Direction;
}

/*=========================================================================================*/
int InitSoko( SOKOSTATE *State, int i, int *soko_x, int *soko_y ) {
/*=========================================================================================*/

    int x, y, s, h, o;
    char *p, *q, *q0, *ips = IMPORTSTRING;

    h = 0;
    x = y = s = -1;
    p = _GameDef[ i ];
    q = q0 = calloc( 512, 1 );

    do {
       if ( *p == '\n' ) {
           if ( x == -1 ) x = ( q - q0 ) + 1;
       } else if (( o = ( (int)strchr( ips, *p ) - (int)ips )) == -(int)ips ) {
           return 0;
       } else if (( o & ~HOMEBIT ) == SKBAN ) {
           *q = (char)(( o & HOMEBIT ) | EMPTY );
           s = q - q0;
           h += o & HOMEBIT;
       } else if (( o & ~HOMEBIT ) == BRICK ) {
           *q = (char)o;
       } else {
           *q = (char)o;
           h += o & HOMEBIT;
       } /* endif */
       p++; q++;
    } while ( *p != NUL ); /* enddo */

    y = ( q - q0 ) / x;

    State->Field   = q0;
    State->CntHome = h;
    State->SizeX   = x;
    State->SizeY   = y;
    State->PosSoko = s;

    *soko_x = s % x;
    *soko_y = s / x;

    State->CntMove = 0;
    State->CntPush = 0;
    State->SizeMove = MOVE_RECORDER_BLOCK_SIZE;
    State->Moves = calloc( State->SizeMove, 1 );

    return 0;
}

/*=========================================================================================*/
char Get1Soko( SOKOSTATE *State, int x, int y ){
/*=========================================================================================*/

    int o;
    char c;

    if ( x < 0 || x >= State->SizeX ) return 0xFF;
    if ( y < 0 || y >= State->SizeY ) return 0xFF;

    o = y * State->SizeX + x;
    c = *( State->Field + o );

    if ( o == State->PosSoko ) c = ( c & 1 ) | SKBAN;
        
    return c;
}

/*=========================================================================================*/
int ExitSoko( SOKOSTATE *State ) {
/*=========================================================================================*/

    free( State->Field );
    free( State->Moves );

    return 0;
}

/* -=EOF=- */
