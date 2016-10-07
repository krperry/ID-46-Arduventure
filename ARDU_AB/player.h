#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

struct Player
{
  int x, y, healthCurrent, healthTotal, gold, experience, experienceForNextLevel;
  byte currentMap, direction, level, attack, attackAddition, defense, defenseAddition, speed, speedAddition, weapon, armor, other;
  unsigned char name[6];
  byte items[ITEMAMOUNT];
  bool tags[1];
};

Player player;


#endif
