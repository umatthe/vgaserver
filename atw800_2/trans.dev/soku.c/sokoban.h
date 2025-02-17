/*
/////////////////////////////////////////////////////////////////////////////////////////////
//
//               S O K O B A N
//
//
//  FILE:        sokoban.h
//
//  PURPOSE:     general includefile with the main constants for sokoban
//
//
//               Copyright (c) 2006 M. Bruestle, Vienna (AT)
//
/////////////////////////////////////////////////////////////////////////////////////////////
*/

#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

    /* coding of the fieldvalues */

    /* modifier (bit 0 ) */

    #define HOMEBIT  1

    /* values   (bit 1&2) */

    #define EMPTY    0
    #define SKBAN    2
    #define BRICK    4
    #define WALL     6

    /* importdefinitions */

    #define IMPORTSTRING " .@+$*#"

    /* the state of the game */

    typedef struct {
       char    *Field;     /* one byte per field ( y * SizeX + x ) */
       char    *Moves;     /* moverecordbuffer for undo/redo */
       size_t   SizeMove;  /* size of moverecordbuffer */
       int      PosSoko    /* where is soko? soko is NOT stored in field */
              , CntMove    /* count of moves  from soko */
              , CntPush    /* count of pushes from soko (move with brick) */
              , CntHome    /* count of unoccupied destination brickfields */
              , SizeX      /* size of game in horizontal direction */
              , SizeY;     /* size of game in vertical direction */
    } SOKOSTATE;

    /* function to operate on bahalf of the state */

    int  InitSoko( SOKOSTATE *State
                 , int       i
                 , int       *soko_x
                 , int       *soko_y );
    char MoveSoko( SOKOSTATE *State
                 , char      *c
                 , char      Direction );
    char UndoSoko( SOKOSTATE *State
                 , char      *c );
    char RedoSoko( SOKOSTATE *State
                 , char      *c );
    char Get1Soko( SOKOSTATE *State
                 , int       x
                 , int       y );
    int  ExitSoko( SOKOSTATE *State );

#endif

/* -=EOF=- */
