#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"

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
    if (selectedLetter > 35)
    {
      player.name[0] = currentLetter;
      if (!currentLetter)
      {
        player.name[0] = 4;
        player.name[1] = 11;
        player.name[2] = 4;
        player.name[3] = 13;
        player.name[4] = 0;
      }
      currentLetter = 0;
      cursorX = 0;
      cursorY = 0;
      gameState = STATE_GAME_PLAYING;
      setPlayer();
      return;
    }
    else
    {
      player.name[currentLetter + 1] = selectedLetter;
      currentLetter = min(currentLetter + 1, 5);
    }
  }

  else if (arduboy.justPressed(A_BUTTON))
  {
    if (currentLetter > 0)
    {
      player.name[currentLetter] = 49;
      currentLetter--;
    }
  }
  
  drawText(labelYourName, 12, 4, BLACK, ALIGN_LEFT, ROM);
  drawText(player.name, 84, 4, BLACK, ALIGN_LEFT, RAM);
  sprites.drawErase(6 + (cursorX * 12), 16 + (cursorY * 10), font, 43);
  drawText(labelEnd, 96, 56, BLACK, ALIGN_LEFT, ROM);
};

void stateGamePlaying()
{
  arduboy.fillScreen(1);
  drawText(player.name, 46, 12, BLACK, ALIGN_LEFT, RAM);
  checkMapInputs();
  drawPlayer();
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
