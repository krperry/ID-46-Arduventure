#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

PROGMEM const unsigned char animSeq[] = { 0, 1, 2, 1 };

struct Player
{
  int x, y, healthCurrent, healthTotal, gold, experience, experienceForNextLevel;
  byte frame, currentMap, direction, level, attack, attackAddition, defense, defenseAddition, speed, speedAddition, weapon, armor, other;
  unsigned char name[6];
  byte items[ITEMAMOUNT];
  boolean tags[1];
  boolean walking;
};

Player player;

void setPlayer()
{
  player.x = 64;
  player.y = 24;
  player.walking = false;
  player.direction = FACING_SOUTH;
  player.frame = 0;
}

void drawPlayer()
{
  if (arduboy.everyXFrames(6) && player.walking) player.frame = (++player.frame) % 4;
  sprites.drawPlusMask(player.x, player.y, player_plus_mask, pgm_read_byte(&animSeq[player.frame]) + 3 * player.direction);
}


#endif
