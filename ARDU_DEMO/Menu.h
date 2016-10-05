byte currentLetter = 0;
byte cursorX = 0;
byte cursorY = 0;
const unsigned char labelYourName[] = {10, 24,14,20,17,NONE,13,0,12,4,39};

bool menuIsVisible = false;
bool menuIsSpecific = false;
byte menuMainChoice = 0;

byte menuItemsChoice = 0;
byte menuItemsListOffset = 0;
byte menuItemsOldAmount = 0;
byte menuItemsLastSelectedItem = 0;

const unsigned char menuLabelItems[] = {5, 8,19,4,12,18};
const unsigned char menuLabelStats[] = {5, 18,19,0,19,18};
const unsigned char menuLabelSave[] = {4, 18,0,21,4};

const unsigned char *menuLabels[] =
{
  menuLabelItems, menuLabelStats, menuLabelSave
};

const unsigned char statsLabels0[] = 
{
  37,
  13,0,12,4,41,
  NEWLINE,
  12,14,13,4,24,41,47,
  NEWLINE,NEWLINE,
  7,15,41,
  NEWLINE,NEWLINE,NEWLINE,
  4,23,15,NONE,19,14,NONE,11,4,21,4,11,NONE,20,15,41,
};

const unsigned char statsLabels1[] = 
{
  19,
  11,21,41,
  NEWLINE,NEWLINE,
  0,19,10,41,
  NEWLINE,
  3,4,5,41,
  NEWLINE,
  18,15,3,41,
};
