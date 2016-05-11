#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte playerFrame = 0;

struct Players
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
};

Players player = { .x = 20, .y = 20, .walking = false, .direction = FACING_SOUTH };

void drawPlayer()
{
  if (arduboy.everyXFrames(6) && player.walking) playerFrame++;
  if (playerFrame > 3 ) playerFrame = 0;
  sprites.drawPlusMask(player.x, player.y, player_plus_mask, playerFrame + 4 * player.direction);
}

#endif
