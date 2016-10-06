#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"

void stateGameLoading()
{

};

void stateGameNew()
{
  byte alphabetX = 16;
  byte alphabetY = 26;
  arduboy.fillScreen(1);
  drawText(labelYourName, 4, 2, BLACK, ALIGN_LEFT, ROM);

  for (byte i = 0; i < 27; i++)
  {
    sprites.drawErase( alphabetX, alphabetY, font, (i < 26) ? i : 50);
    alphabetX += 12;
    if (alphabetX == 124)
    {
      alphabetY += 12;
      alphabetX = 16;
    }
  }
  if (arduboy.justPressed(UP_BUTTON)) cursorY += (cursorY > 0) ? -1 : 2;
  else if (arduboy.justPressed(DOWN_BUTTON)) cursorY += (cursorY < 2) ? 1 : -2;
  else if (arduboy.justPressed(LEFT_BUTTON)) cursorX += (cursorX > 0) ? -1 : 8;
  else if (arduboy.justPressed(RIGHT_BUTTON)) cursorX += (cursorX < 8) ? 1 : -8;

  else if (arduboy.justPressed(B_BUTTON))
  {
    byte selectedLetter = cursorX + (cursorY * 9);
    if (selectedLetter > 25)
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
  sprites.drawErase(10 + (cursorX * 12), 26 + (cursorY * 12), font, 43);
  drawText(playerName, 46, 14, BLACK, ALIGN_LEFT, RAM);
};

void stateGamePlaying()
{
  drawText(playerName, 46, 14, WHITE, ALIGN_LEFT, RAM);
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
