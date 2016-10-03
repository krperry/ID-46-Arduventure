#define TRIGGERTYPE_TEXTBOX 0
#define TRIGGERTYPE_ITEM 1

struct Trigger
{
  byte type, value, map, x, y, options; // Options = active, useOnce, chest, ...
};

const byte TRIGGERAMOUNT = 8;
Trigger triggers[TRIGGERAMOUNT] =
{
  {TRIGGERTYPE_TEXTBOX, 0, 0, 5, 4, 0b00000001}, // Arduvillage sign
  {TRIGGERTYPE_TEXTBOX, 1, 0, 7, 3, 0b00000001}, // Fishing rod guy
  
  {TRIGGERTYPE_ITEM, ITEM_DAGGER, 1, 4, 1, 0b00000111}, // Chest
  {TRIGGERTYPE_TEXTBOX, 7, 1, 1, 1, 0b00000001}, // Bed

  {TRIGGERTYPE_TEXTBOX, 2, 2, 2, 2, 0b00000001}, // Shop Buy Guy
  {TRIGGERTYPE_TEXTBOX, 3, 2, 5, 2, 0b00000001}, // Shop Sell Guy

  {TRIGGERTYPE_TEXTBOX, 14, 5, 3, 1, 0b00000001}, // Bridge broken Guy
  
  {TRIGGERTYPE_TEXTBOX, 15, 4, 3, 1, 0b00000001} // Endless woods sign
};
