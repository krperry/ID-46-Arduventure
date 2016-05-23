#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include "globals.h"
#include "player.h"

void checkInputs()
{
  player.walking = false;
  if (arduboy.pressed(DOWN_BUTTON) && (player.y < GAME_BOTTOM))
  {
    player.direction = FACING_SOUTH;
    player.y++;
    player.walking = true;
  }
  if (arduboy.pressed(LEFT_BUTTON) && (player.x > GAME_LEFT))
  {
    player.direction = FACING_WEST;
    player.x--;
    player.walking = true;
  }
  if (arduboy.pressed(UP_BUTTON) && (player.y > GAME_TOP))
  {
    player.direction = FACING_NORTH;
    player.y--;
    player.walking = true;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && (player.x < GAME_RIGHT))
  {
    player.direction = FACING_EAST;
    player.x++;
    player.walking = true;
  }

  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PAUSE;
  if (arduboy.justPressed(B_BUTTON)) arduboy.audio.tone(880, 20);
}


#endif
