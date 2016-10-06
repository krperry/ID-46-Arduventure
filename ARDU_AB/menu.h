#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
#include "text.h"
#include "player.h"

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  sprites.drawSelfMasked(36, 3, aTeamArgGame, 0);
  sprites.drawSelfMasked(10, 10, titleScreen, 0);
  drawText(labelContinue, 40, 37, WHITE, ALIGN_LEFT, RAM);
  drawText(labelNewGame, 40, 46, WHITE, ALIGN_LEFT, ROM);
  if (arduboy.audio.enabled()) drawText(labelSndOn, 40, 55, WHITE, ALIGN_LEFT, ROM);
  else drawText(labelSndOff, 40, 55, WHITE, ALIGN_LEFT, ROM);
  sprites.drawSelfMasked( 32, 37 + (menuSelection - 2) * 9, font, 43);
  sprites.drawSelfMasked( 90, 37 + (menuSelection - 2) * 9, font, 44);
  if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < 4)) menuSelection++;
  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (arduboy.justPressed(B_BUTTON)) gameState = menuSelection;
}

void stateMenuContinue()
{

}

void stateMenuNew()
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
    if (cursorX + (cursorY * 9) > 25)
    {
      if (currentLetter == 0)
      {
        playerName[0] = 4;
        playerName[1] = 11;
        playerName[2] = 4;
        playerName[3] = 13;
        playerName[4] = 0;
      }
      gameState = STATE_GAME_PLAYING;

      currentLetter = 0;
      cursorX = 0;
      cursorY = 0;

      return;
    }
    else
    {
      playerName[currentLetter + 1] = cursorX + (cursorY * 9);
      currentLetter = min(currentLetter + 1, 5);
    }
  }

  
  else if (arduboy.justPressed(A_BUTTON))
  {
    if (currentLetter > 0)
    {
      currentLetter--;
      playerName[currentLetter + 1] = NONE;
    }
  }
  playerName[0] = currentLetter;

  sprites.drawErase(10 + (cursorX * 12), 26 + (cursorY * 12), font, 43);

  for (byte i = currentLetter; i < 5; i++)
  {
    sprites.drawErase(46 + (i * 6), 14, font, 49);
  }

  drawText(playerName, 46, 14, BLACK, ALIGN_LEFT, RAM);
}

void stateMenuSound()
{
  if (arduboy.audio.enabled()) arduboy.audio.off();
  else arduboy.audio.on();
  arduboy.audio.saveOnOff();
  gameState = STATE_MENU_MAIN;
}


#endif
