#define BATTLESTATE_ACTIONCHOICE 0
#define BATTLESTATE_ENEMYCHOICE 1
#define BATTLESTATE_PLAYERATTACKING 2
#define BATTLESTATE_ENEMIESDAMAGING 3
#define BATTLESTATE_ENEMIESATTACKING 4
#define BATTLESTATE_PLAYERDAMAGING 5
#define BATTLESTATE_WON 6
#define BATTLESTATE_END 7

byte battleState = BATTLESTATE_ACTIONCHOICE;
byte battleStartEffectCounter = 0;
byte battleStartEffectToggle = false;

byte battleDamageEffectCounter = 0;
byte battleDamageEffectToggle = true;

byte currentActionChoice = 0;
byte currentEnemyChoice = 0;
byte currentEnemyTurn = 0;
byte changedChoice = false;

const unsigned char battleChoices[] =
{
  18,
  0,19,19,0,2,10,NONE,NONE,8,19,4,12,18,NONE,NONE,17,20,13
};

const unsigned char battleChoicePositions[] =
{
  4, 52, 94
};

//------------------------
// Battle formations
//------------------------
byte currentBattleFormation, currentEnemyAmount;
byte currentEnemies[4];
int currentEnemyHealth[4];

const unsigned char PROGMEM battleFormation0[] = {3, 0, 1, 0};
const unsigned char PROGMEM battleFormation1[] = {2, 1, 0};
const unsigned char PROGMEM battleFormation2[] = {1, 2};
const unsigned char PROGMEM battleFormation3[] = {4, 0, 0, 0, 0};
const unsigned char PROGMEM battleFormation4[] = {3, 2, 2, 2};

const byte BATTLEFORMATIONAMOUNT = 4;
const unsigned char *battleFormations[] =
{
  battleFormation0, battleFormation1, battleFormation2, battleFormation3, battleFormation4
};

//------------------------
// Enemies
//------------------------

// Struct
struct Enemy
{
    int id, health, attack, defense, speed, exp, gold;
};

const byte ENEMYAMOUNT = 3;
const Enemy enemies[] =
{
  {0, 7, 5, 0, 1, 5, 2}, // Worm
  {1, 10, 7, 1, 1, 8, 8}, // Beetle
  {2, 12, 8, 3, 1, 15, 15}  // Bird
};

// Bitmaps
const unsigned char PROGMEM enemyBitmaps[][32] =
{
  {0x00,0x00,0x00,0xf8,0xa4,0x82,0xa2,0x92,0x04,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x34,0x64,0x64,0x72,0x6f,0x38,0x38,0x1c,0x0c,0x00,0x00},
  {0x00,0xe0,0x98,0x44,0x32,0x2a,0x21,0x21,0x31,0x49,0x82,0x02,0xc4,0xe8,0x70,0x80,0xee,0x99,0x6f,0x1c,0x25,0x3a,0x18,0x3a,0x25,0x1c,0x6f,0x9f,0xe7,0x0d,0x13,0x1d},
  {0xc0,0x20,0x1c,0x12,0xa1,0xd1,0x89,0x09,0x02,0x3c,0x50,0x48,0x5c,0x44,0x78,0xc0,0x01,0xc2,0xa4,0xdf,0xba,0xf1,0x70,0xf0,0xba,0xdc,0x98,0xb8,0x58,0x09,0x05,0x03},
};

// Names
const unsigned char name0[] = {4, 22,14,17,12};
const unsigned char name1[] = {6, 1,4,4,19,11,4};
const unsigned char name2[] = {4, 1,8,17,3};


const unsigned char *enemyNames[] =
{
  name0, name1, name2
};

const unsigned char labelHealth[] = {3, 7,15,41};
