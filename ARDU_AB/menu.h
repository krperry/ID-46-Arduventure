#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
#include "text.h"

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
  drawText(labelContinue, 40, 37, WHITE, ALIGN_LEFT);
  drawText(labelNewGame, 40, 45, WHITE, ALIGN_LEFT);
  drawText(labelSndOff, 40, 53, WHITE, ALIGN_LEFT);
  //gameState = menuSelection;
}



#endif
