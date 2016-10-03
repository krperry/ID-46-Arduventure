#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "globals.h"

#define NONE                          255
#define NEWLINE                       254
#define ALIGN_LEFT                    0
#define ALIGN_RIGHT                   1

const unsigned char labelContinue[] = {8, 2,14,13,19,8,13,20,4};
const unsigned char labelNewGame[] = {8, 13,4,22,NONE,6,0,12,4};

void drawText(const unsigned char *text, byte x, byte y, byte color, byte alignment)
{
  byte xOffset = 0;
  byte yOffset = 0;
  
  for(byte i = 0; i < text[0]; i++)
  {
    if(text[i + 1] == NEWLINE)
    {
      yOffset += 6;
      xOffset = 0;
    }
    else
    {
      if(text[i + 1] != NONE) sprites.drawSelfMasked(x - ((alignment == ALIGN_RIGHT)?((text[0] - 1) * 6):0) + xOffset, y + yOffset, font, text[i + 1]);
      xOffset += 6;
    }
  }
}

#endif
