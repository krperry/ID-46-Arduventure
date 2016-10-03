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
  sprites.drawSelfMasked(10, 8, titleScreen, 0);
  drawText(labelContinue, 40, 32, WHITE, ALIGN_LEFT);
  drawText(labelNewGame, 40, 44, WHITE, ALIGN_LEFT);
  //gameState = menuSelection;
}



#endif
