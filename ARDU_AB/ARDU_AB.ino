/*
  ARDUVENTURE: http://www.team-arg.org/ardu-manual.html
  
  Arduboy version 0.1:  http://www.team-arg.org/ardu-downloads.html
  
  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html
  
  2016 - SIEGFRIED CROES - JO3RI
  
  License: MIT : https://opensource.org/licenses/MIT
*/

//determine the game
#define GAME_ID 46

#include "Arglib.h"
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "text.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateGamePlaying,
  stateGameInventory,
  stateGameOver,
};


void setup() {
  arduboy.start();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.poll();
  arduboy.clearDisplay();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

