/*
  GAME NAME: http://www.team-arg.org/dummy-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/dummy-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016 - JO3RI

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 00

#include "Arglib.h"
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "elements.h"
#include "enemies.h"
#include "levels.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePrepareLevel,
  stateGameNextLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};


void setup() {
  arduboy.start();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  gameState = STATE_MENU_INTRO;                             // start the game with the TEAM a.r.g. logo
  menuSelection = STATE_MENU_PLAY;                          // PLAY menu item is pre-selected
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;  // check EEPROM if sound is OFF or ON
  arduboy.initRandomSeed();
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

