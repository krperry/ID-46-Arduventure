#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "Arglib.h"
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1

//define game states (on main menu)
#define STATE_GAME_LOADING           3
#define STATE_GAME_NEW               4
#define STATE_GAME_PLAYING           5
#define STATE_GAME_INVENTORY         6
#define STATE_GAME_OVER              7

#define FACING_SOUTH                 0
#define FACING_WEST                  1
#define FACING_NORTH                 2
#define FACING_EAST                  3

Arduboy arduboy;
Sprites sprites(arduboy);

byte gameState = STATE_MENU_INTRO;          // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_GAME_LOADING;    // PLAY menu item is pre-selected
byte globalCounter = 0;

#endif
