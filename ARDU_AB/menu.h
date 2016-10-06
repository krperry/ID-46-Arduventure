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
  drawText(labelContinue, 40, 37, WHITE, ALIGN_LEFT, ROM);
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
  for (byte i = 0; i < 6; i++) playerName[i] = (i == 0) ? 5:49;
  gameState = STATE_GAME_NEW;
}

void stateMenuSound()
{
  if (arduboy.audio.enabled()) arduboy.audio.off();
  else arduboy.audio.on();
  arduboy.audio.saveOnOff();
  gameState = STATE_MENU_MAIN;
}


#endif
