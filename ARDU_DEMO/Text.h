#define NEWLINE 254
#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1

//------------------------
// VARIABLES
//------------------------
bool textboxIsVisible = false;
bool textboxIsComplete = false;
byte textboxIsDynamic = false;
bool textboxIsChoice = true;
byte textboxCurrentText = 0;
byte textboxCurrentProgress = 0;
byte textboxCurrentChoice = 0;

//------------------------
// FONT
//------------------------

const unsigned char PROGMEM font[][5]
{
  {0x1e,0x05,0x05,0x05,0x1e},
  {0x1f,0x15,0x15,0x15,0x0a},
  {0x0e,0x11,0x11,0x11,0x0a},
  {0x1f,0x11,0x11,0x11,0x0e},
  {0x1f,0x15,0x15,0x15,0x11},
  {0x1f,0x05,0x05,0x05,0x01},
  {0x0e,0x11,0x11,0x15,0x1d},
  {0x1f,0x04,0x04,0x04,0x1f},
  {0x00,0x11,0x1f,0x11,0x00},
  {0x10,0x11,0x0f,0x01,0x00},
  {0x1f,0x04,0x04,0x0a,0x11},
  {0x1f,0x10,0x10,0x10,0x10},
  {0x1f,0x02,0x04,0x02,0x1f},
  {0x1f,0x02,0x04,0x08,0x1f},
  {0x0e,0x11,0x11,0x11,0x0e},
  {0x1f,0x05,0x05,0x05,0x02},
  {0x0e,0x11,0x11,0x09,0x16},
  {0x1f,0x05,0x05,0x0d,0x12},
  {0x12,0x15,0x15,0x15,0x09},
  {0x01,0x01,0x1f,0x01,0x01},
  {0x0f,0x10,0x10,0x10,0x0f},
  {0x03,0x0c,0x10,0x0c,0x03},
  {0x1f,0x08,0x04,0x08,0x1f},
  {0x11,0x0a,0x04,0x0a,0x11},
  {0x01,0x02,0x1c,0x02,0x01},
  {0x11,0x19,0x15,0x13,0x11},
  {0x0e,0x19,0x15,0x13,0x0e},
  {0x00,0x12,0x1f,0x10,0x00},
  {0x19,0x15,0x15,0x15,0x12},
  {0x11,0x15,0x15,0x15,0x0a},
  {0x07,0x04,0x04,0x1e,0x04},
  {0x17,0x15,0x15,0x15,0x09},
  {0x0e,0x15,0x15,0x15,0x08},
  {0x01,0x01,0x19,0x05,0x03},
  {0x0a,0x15,0x15,0x15,0x0a},
  {0x02,0x15,0x15,0x15,0x0e},
  {0x00,0x00,0x10,0x00,0x00},
  {0x00,0x20,0x10,0x00,0x00},
  {0x00,0x00,0x17,0x00,0x00},
  {0x00,0x01,0x15,0x03,0x00},
  {0x00,0x00,0x03,0x00,0x00},
  {0x00,0x12,0x00,0x00,0x00},
  {0x10,0x08,0x04,0x02,0x01},
  {0x00,0x1f,0x1f,0x0e,0x04},
  {0x0c,0x0a,0x09,0x0a,0x0c},
  {0x06,0x0a,0x12,0x0a,0x06},
  {0x04,0x0e,0x1f,0x0e,0x04},
  {0x04,0x0e,0x15,0x1d,0x04},
  {0x10,0x10,0x10,0x10,0x10},
  {0x04,0x04,0x15,0x0e,0x04},
  {0x00,0x00,0x0e,0x11,0x00},
  {0x00,0x00,0x11,0x0e,0x00},
  {0x00,0x04,0x0e,0x04,0x00},
  {0x00,0x04,0x04,0x04,0x00}
};

//------------------------
// TEXTBOXES
//------------------------

// TextLength, NewlinePosition, NextTextbox/Result, IsChoice

const unsigned char PROGMEM signText0[] = // WELCOME TO ARDUVILLAGE!
{
  22, 9, NONE, 0,
  22,4,11,2,14,12,4,NONE,19,14,0,17,3,20,21,8,11,11,0,6,4,38
};

const unsigned char PROGMEM npcText0[] = // I WISH I HAD A FISHING ROD...
{
  28, 13, NONE, 0,
  8,NONE,22,8,18,7,NONE,8,NONE,7,0,3,NONE,0,5,8,18,7,8,13,6,NONE,17,14,3,36,36,36
};

const unsigned char PROGMEM shopBuyText[] = // WHAT DO YOU NEED?
{
  17, NONE, 129, 0,
  22,7,0,19,NONE,3,14,NONE,24,14,20,NONE,13,4,4,3,39
};

const unsigned char PROGMEM shopSellText[] = // WHAT WOULD YOU LIKE TO SELL?
{
  27, 13, 130, 0,
  22,7,0,19,NONE,22,14,20,11,3,NONE,24,14,20,11,8,10,4,NONE,19,14,NONE,18,4,11,11,39
};

const unsigned char PROGMEM battleText0[] = // CAN'T ESCAPE!
{
  13, 20, NONE, 0,
  2,0,13,40,19,NONE,4,18,2,0,15,4,38
};

const unsigned char PROGMEM battleText1[] = // GOT AWAY SAFELY!
{
  16, 20, NONE, 0,
  6,14,19,NONE,0,22,0,24,NONE,18,0,5,4,11,24,38
};

const unsigned char PROGMEM battleText2[] = // YOU WIN!
{
  8, 20, NONE, 0,
  24,14,20,NONE,22,14,13,38
};

const unsigned char PROGMEM sleepText[] = // SLEEP TO RESTORE ALL HEALTH?
{
  6, NONE, 128, 1,
  18,11,4,4,15,39
};

const unsigned char PROGMEM saveText[] = // SAVE PROGRESS?
{
  14, 20, 132, 1,
  18,0,21,4,NONE,15,17,14,6,17,4,18,18,39
};

const unsigned char PROGMEM useText[] = // USE?
{
  4, NONE, 131, 1,
  20,18,4,39
};

const unsigned char PROGMEM equipText[] = // EQUIP?
{
  6, NONE, 131, 1,
  4,16,20,8,15,39
};

const unsigned char PROGMEM unequipText[] = // UNEQUIP?
{
  8, NONE, 131, 1,
  20,13,4,16,20,8,15,39
};

const unsigned char PROGMEM forbiddenText[] = // THAT'S FORBIDDEN IN THE DEMO!
{
  28, 15, NONE, 0,
  19,7,0,19,40,18,NONE,5,14,17,1,8,3,3,4,13,8,13,NONE,19,7,4,NONE,3,4,12,14,38
};

const unsigned char PROGMEM levelUpText[] = // LEVEL UP!!!
{
  11, NONE, NONE, 0,
  11,4,21,4,11,NONE,20,15,38,38,38
};

const unsigned char PROGMEM bridgeBrokenText[] = // THE BRIDGE IS BROKEN...
{
  22, 12, NONE, 0,
  19,7,4,NONE,1,17,8,3,6,4,NONE,8,18,1,17,14,10,4,13,36,36,36
};

const unsigned char PROGMEM woodsSignText[] = // ENDLESS WOODS AHEAD...
{
  19, 12, NONE, 0,
  4,13,3,11,4,18,18,NONE,22,14,14,3,18,0,7,4,0,3,38
};

const unsigned char *texts[] =
{
  signText0, // 0
  npcText0, // 1
  shopBuyText, // 2
  shopSellText, // 3
  battleText0, // 4
  battleText1, // 5
  battleText2, // 6
  sleepText, // 7
  saveText, // 8
  useText, // 9
  equipText, // 10
  unequipText, // 11
  forbiddenText, // 12
  levelUpText, // 13
  bridgeBrokenText, // 14
  woodsSignText // 15
};

const unsigned char YesNoLabels[] = {6, 24,4,18,NEWLINE,13,14};

//------------------------
// DYNAMIC TEXT STUFF
//------------------------

unsigned char dynamicTextbox[44];
unsigned char dynamicText[41];
unsigned char dynamicNumber[9];

const unsigned char wordFound[] = {5,14,20,13,3};
const unsigned char wordBuy[] = {1,20,24,NONE,27,NONE,5,14,17,NONE};
const unsigned char wordSell[] = {18,4,11,11,NONE,27,NONE,5,14,17,NONE};

const unsigned char wordHealth0[] = {17,4,18,19,14,17,4,18,NONE};
const unsigned char wordHealth1[] = {7,15};

const unsigned char wordWeapon0[] = {22,4,0,15,14,13,NONE,50,52};
const unsigned char wordArmor0[] = {0,17,12,14,17,NONE,50,52};
const unsigned char wordWeaponArmor1[] = {51, NEWLINE};

const unsigned char wordAttacks[] = {0,19,19,0,2,10,18,38};
const unsigned char wordTakes[] = {19,0,10,4,18};
const unsigned char wordDamage[] = {3,0,12,0,6,4,38};
const unsigned char wordFainted[] = {5,0,8,13,19,4,3,38};

const unsigned char wordGainedExp0[] = {6,0,8,13,4,3};
const unsigned char wordGainedExp1[] = {4,23,15,38};
