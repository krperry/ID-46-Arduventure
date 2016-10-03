#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"

void stateGameLoading()
{

};

void stateGameNew()
{

};

void stateGamePlaying()
{

};

void stateGameInventory()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{
  
};



#endif
