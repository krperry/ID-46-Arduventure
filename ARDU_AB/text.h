#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "globals.h"

#define NONE                          255
#define NEWLINE                       254
#define ALIGN_LEFT                    0
#define ALIGN_RIGHT                   1

PROGMEM const unsigned char labelContinue[] = {8, 2, 14, 13, 19, 8, 13, 20, 4};
PROGMEM const unsigned char labelNewGame[] = {8, 13, 4, 22, NONE, 6, 0, 12, 4};
PROGMEM const unsigned char labelSndOff[] = {8, 18, 13, 3, NONE, NONE, 14, 5, 5};
PROGMEM const unsigned char labelSndOn[] = {8, 18, 13, 3, NONE, NONE, NONE, 14, 13};
PROGMEM const unsigned char labelYourName[] = {10, 24, 14, 20, 17, NONE, 13, 0, 12, 4, 39};

void drawText(const unsigned char *text, byte x, byte y, byte color, byte alignment)
{
  byte xOffset = 0;
  byte yOffset = 0;
  byte sizeText = pgm_read_byte(text);

  for (byte i = 0; i < sizeText; i++)
  {
    text++;
    if (pgm_read_byte(text) == NEWLINE)
    {
      yOffset += 6;
      xOffset = 0;
    }
    else if (pgm_read_byte(text) != NONE)
    {
      if (color)sprites.drawSelfMasked(x - ((alignment == ALIGN_RIGHT) ? ((sizeText - 1) * 6) : 0) + xOffset, y + yOffset, font, pgm_read_byte(text));
      else sprites.drawErase(x - ((alignment == ALIGN_RIGHT) ? ((sizeText - 1) * 6) : 0) + xOffset, y + yOffset, font, pgm_read_byte(text));
    }
    xOffset += 6;
  }
}

#endif
