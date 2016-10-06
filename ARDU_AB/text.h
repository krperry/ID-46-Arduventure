#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "globals.h"

#define NONE                          255
#define NEWLINE                       254
#define ALIGN_LEFT                    0
#define ALIGN_RIGHT                   1
#define RAM                           0
#define ROM                           1

PROGMEM const unsigned char labelContinue[] = {8, 2, 14, 13, 19, 8, 13, 20, 4};
PROGMEM const unsigned char labelNewGame[] = {8, 13, 4, 22, NONE, 6, 0, 12, 4};
PROGMEM const unsigned char labelSndOff[] = {8, 18, 13, 3, NONE, NONE, 14, 5, 5};
PROGMEM const unsigned char labelSndOn[] = {8, 18, 13, 3, NONE, NONE, NONE, 14, 13};
//PROGMEM const unsigned char labelYourName[] = {36, 19,4,11,11,NONE,20,18,NONE,24, 14, 20, 17, NONE, 13, 0, 12, 4,NEWLINE,1,17,0,21,4,NONE,0,17,3,20,21,4,13,19,20,17,4,17};
//PROGMEM const unsigned char labelYourName[] = {19, 22,7,0,19,NONE,8,18,NONE,24, 14, 20, 17, NONE, 13, 0, 12, 4,NONE,39};
PROGMEM const unsigned char labelYourName[] = {10, 24, 14, 20, 17, NONE, 13, 0, 12, 4,41};
PROGMEM const unsigned char labelEnd[] = {3, 4,13,3};



void drawText(const unsigned char *text, byte x, byte y, byte color, byte alignment, boolean romOrRam)
{
  byte xOffset = 0;
  byte yOffset = 0;
  byte sizeText = (romOrRam == ROM) ? pgm_read_byte(text) : text[0] ;

  for (byte i = 1; i < sizeText + 1; i++)
  {
    if (romOrRam == ROM)text++;
    if ((romOrRam == ROM) ? pgm_read_byte(text) == NEWLINE : (text[i]) == NEWLINE)
    {
      yOffset += 6;
      xOffset = -6;
    }
    else if ((romOrRam == ROM) ? pgm_read_byte(text) != NONE : (text[i]) != NONE)
    {
      if (color)sprites.drawSelfMasked(x - ((alignment == ALIGN_RIGHT) ? ((sizeText - 1) * 6) : 0) + xOffset, y + yOffset, font, (romOrRam == ROM) ? pgm_read_byte(text) : text[i]);
      if (!color)sprites.drawErase(x - ((alignment == ALIGN_RIGHT) ? ((sizeText - 1) * 6) : 0) + xOffset, y + yOffset, font, (romOrRam == ROM) ? pgm_read_byte(text) : text[i]);
    }
    xOffset += 6;
  }
}

#endif
