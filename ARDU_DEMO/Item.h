#define ITEMTYPE_HEALTH 0
#define ITEMTYPE_WEAPON 1
#define ITEMTYPE_ARMOR 3
#define ITEMTYPE_OTHER 5

#define ITEM_APPLE 0
#define ITEM_POTION 1
#define ITEM_HEALSTONE 2
#define ITEM_DAGGER 3
#define ITEM_SHORTSWORD 4
#define ITEM_IRONARMOR 5

//------------------------
// ITEM NAMES
//------------------------

const unsigned char itemName0[] = {5, 0,15,15,11,4}; // Apple
const unsigned char itemName1[] = {6, 15,14,19,8,14,13}; // Potion
const unsigned char itemName2[] = {9, 7,4,0,11,18,19,14,13,4}; // Heal Stone
const unsigned char itemName3[] = {6, 3,0,6,6,4,17}; // Dagger
const unsigned char itemName4[] = {11, 18,7,14,17,19,NONE,18,22,14,17,3}; // Short Sword
const unsigned char itemName5[] = {10, 8,17,14,13,NONE,0,17,12,14,17}; // Iron Armor

//------------------------
// ITEM OBJECTS
//------------------------

struct Item
{
  const unsigned char *name;
  byte type;
  int value;
  int price;
};

const byte ITEMAMOUNT = 6;
const Item items[] =
{
  {itemName0, ITEMTYPE_HEALTH, 5, 5},
  {itemName1, ITEMTYPE_HEALTH, 20, 20},
  {itemName2, ITEMTYPE_HEALTH, 100, 100},
  {itemName3, ITEMTYPE_WEAPON, 2, 100},
  {itemName4, ITEMTYPE_WEAPON, 5, 500},
  {itemName5, ITEMTYPE_ARMOR, 2, 400},
};

//------------------------
// OTHER
//------------------------

const unsigned char itemNone[] = {8, 13,14,NONE,8,19,4,12,18}; // No items
