#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"

void stateGameLoading()
{

};

void stateGameNew()
{
  byte alphabetX = 12;
  byte alphabetY = 16;
  arduboy.fillScreen(1);
  
  for (byte i = 0; i < 36; i++)
  {
    sprites.drawErase( alphabetX, alphabetY, font, i);
    alphabetX += 12;
    if (alphabetX > 119)
    {
      alphabetY += 10;
      alphabetX = 12;
    }
  }
  
  if (arduboy.justPressed(UP_BUTTON)) cursorY += (cursorY > 0) ? -1 : 4;
  else if (arduboy.justPressed(DOWN_BUTTON)) cursorY += (cursorY < 4) ? 1 : -4; 
  else if (arduboy.justPressed(LEFT_BUTTON))cursorX += (cursorX > 0) ? -1 : 8;
  else if (arduboy.justPressed(RIGHT_BUTTON)) cursorX += (cursorX < 8) ? 1 : -8;
  if (cursorY == 4) cursorX = 7;
  if (arduboy.justPressed(B_BUTTON))
  {
    byte selectedLetter = cursorX + (cursorY * 9);
    if (selectedLetter > 34)
    {
      playerName[0] = currentLetter;
      if (!currentLetter)
      {
        playerName[0] = 4;
        playerName[1] = 11;
        playerName[2] = 4;
        playerName[3] = 13;
        playerName[4] = 0;
      }
      currentLetter = 0;
      cursorX = 0;
      cursorY = 0;
      gameState = STATE_GAME_PLAYING;
      return;
    }
    else
    {
      playerName[currentLetter + 1] = selectedLetter;
      currentLetter = min(currentLetter + 1, 5);
    }
  }

  else if (arduboy.justPressed(A_BUTTON))
  {
    if (currentLetter > 0)
    {
      playerName[currentLetter] = 49;
      currentLetter--;
    }
  }
  
  drawText(labelYourName, 12, 4, BLACK, ALIGN_LEFT, ROM);
  drawText(playerName, 84, 4, BLACK, ALIGN_LEFT, RAM);
  sprites.drawErase(6 + (cursorX * 12), 16 + (cursorY * 10), font, 43);
  drawText(labelEnd, 96, 56, BLACK, ALIGN_LEFT, ROM);
};

void stateGamePlaying()
{
  drawText(playerName, 46, 12, WHITE, ALIGN_LEFT, RAM);
  if (arduboy.justPressed(B_BUTTON)) gameState = STATE_MENU_MAIN;
};

void stateGameInventory()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{

};



#endif
