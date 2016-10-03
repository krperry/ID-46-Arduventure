/*
  ARDUVENTURE: http://www.team-arg.org/ardu-manual.html
  
  Arduboy version 0.1:  http://www.team-arg.org/ardu-downloads.html
  
  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html
  
  2016 - SIEGFRIEDCROES
  
  License: MIT : https://opensource.org/licenses/MIT
*/

//determine the game
#define GAME_ID 46

#include "Arglib.h"
#include "globals.h"
#include "game.h"

#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "title.h"
#include "item.h"
#include "player.h"
#include "map.h"
#include "trigger.h"
#include "text.h"
#include "menu.h"
#include "shop.h"
#include "battle.h"

#define STATE_TITLE 0
#define STATE_ENTERNAME 1
#define STATE_GAMEPLAY 2
#define STATE_SHOP 3
#define STATE_BATTLE 4
#define STATE_TRANSITION 5
#define STATE_GAMEOVER 6

byte state = STATE_TITLE;
byte nextState = STATE_ENTERNAME;

byte randomCounter = 0;

byte buttons = 0;

void setup()
{
  resetPlayer();

  //Serial.begin(9600);
}

void loop() 
{
  if(!arduboy.nextFrame()) return;
   arduboy.clearDisplay();

  if(state == STATE_TITLE)
  {
    arduboy.drawBitmap(10, 8, title, 109, 16, WHITE);

    if(checkLoad())
    {
      drawText(labelContinue, 40, 32, WHITE, ALIGN_LEFT);

      if(getButtonDown(UP_BUTTON) || getButtonDown(DOWN_BUTTON))
      {
        titleChoice = (titleChoice)?0:1;
      }
    }
    
    drawText(labelNewGame, 40, (checkLoad())?44:32, WHITE, ALIGN_LEFT);
    arduboy.drawBitmap(34, 32 + (titleChoice * 12), font[43], 5, 5, WHITE);

    if(arduboy.pressed(B_BUTTON))
    {
      if(checkLoad() && titleChoice == 0)
      {
        load();
        nextState = STATE_GAMEPLAY;
      }
      else nextState = STATE_ENTERNAME;
      
      state = STATE_TRANSITION;
      titleChoice = 0;
    }
  }
  else if(state == STATE_ENTERNAME) doEnterName();
  else if(state == STATE_GAMEPLAY)
  {    
    if(battleStartEffectCounter > 0)
    {
      if(--battleStartEffectCounter % 4 == 0) battleStartEffectToggle = !battleStartEffectToggle;   
      if(battleStartEffectToggle) arduboy.fillRect(0, 0, 128, 64, WHITE);

      if(battleStartEffectCounter == 0)
      {
        state = STATE_TRANSITION;
        nextState = STATE_BATTLE;
      }
    }
    else
    {
      if(!textboxIsVisible && !menuIsVisible)
      {
        updatePlayer();
        updateScene();
      }
    }

    if(!menuIsSpecific)
    {
      drawScene();
      drawPlayer();
    }
  }
  else if(state == STATE_SHOP)
  {
    drawText((shopState == SHOPSTATE_BUY)?labelShopBuy:labelShopSell, 4, 2, WHITE, ALIGN_LEFT);

    generateGoldText();
    drawText(dynamicText, 120, 2, WHITE, ALIGN_RIGHT);
    
    arduboy.fillRect(0, 10, 128, 36, WHITE);
    doItemList();

    if(!textboxIsVisible && getButtonDown(A_BUTTON)) state = STATE_GAMEPLAY;
  }
  else if(state == STATE_BATTLE)
  {
    drawBattle();
    updateBattle();
  }
  else if(state == STATE_GAMEOVER)
  {
    drawText(labelGameOver, 37, 26, WHITE, ALIGN_LEFT);

    if(arduboy.pressed(B_BUTTON))
    {
      nextState = STATE_TITLE;
      state = STATE_TRANSITION;
    }
  }
  else if(state == STATE_TRANSITION)
  {
    arduboy.display();
    delay(800);
    state = nextState;
  }
  
  if(menuIsVisible) doMenu();
  if(textboxIsVisible) doTextbox();

  if(state != STATE_TRANSITION) arduboy.display();
}

void drawPlayer()
{
  arduboy.drawBitmap(player.x - camX, player.y - camY, playerMasks[player.direction + animSeq[playerFrame]], 16, 16, BLACK);
  arduboy.drawBitmap(player.x - camX, player.y - camY, playerBitmaps[player.direction + animSeq[playerFrame]], 16, 16, WHITE);
}

void updatePlayer()
{
  if(arduboy.everyXFrames(8)) playerFrame = ++playerFrame % 4;

  for(byte i = 0; i < 4; i++)
  {
    if(arduboy.pressed(playerMovement[i][0]))
    {
      player.direction = playerMovement[i][1];

      if(checkSpaceFree(playerMovement[i][2], playerMovement[i][3]))
      {
        player.x += playerMovement[i][2];
        player.y += playerMovement[i][3];

        playerSteps++;
      }

      checkForDoors();

      return;
    }
  }
  
  playerFrame = 1;
}

bool checkSpaceFree(int8_t offsetX, int8_t offsetY)
{
  byte x = 0;
  byte y = 0;

  for(int i = 0; i < 4; i++)
  {
    int gridX = (player.x + playerCollision[i][0] + offsetX) / 64;
    int gridY = (player.y + playerCollision[i][1] + offsetY) / 64;
    
    byte id = pgm_read_byte(&world[gridY][gridX]);

    byte xPos = (((player.x + playerCollision[i][0] + offsetX) - (gridX * 64)) / 16);
    byte yPos = ((((player.y + playerCollision[i][1] + offsetY) - (gridY * 64)) / 16) * 4);

    if(pgm_read_byte(&blocks[id - 1][xPos + yPos]) > 7) return false;
  }
  
  if(player.currentMap > 0)
  {
    if((player.x + 2 + offsetX) < (player.currentMap - 1) * 128 || (player.x + 14 + offsetX) > ((player.currentMap - 1) * 128) + 128) return false;
    else if((player.y + 7 + offsetY) < 2048 || (player.y + 16 + offsetY) > 2048 + 64) return false;
  }

  return true;
}

bool checkForDoors()
{
  for(byte i = 0; i < DOORSAMOUNT; i++)
  {
    if(doors[i].locationMap == player.currentMap)
    {
      if((player.x + 8) / 16 == doors[i].locationX && (player.y + 8) / 16 == doors[i].locationY)
      {
        player.currentMap = doors[i].destinationMap;
        
        player.x = doors[i].destinationX * 8;
        player.y = doors[i].destinationY * 8;

        playerSteps = 0;
        
        state = STATE_TRANSITION;
        nextState = STATE_GAMEPLAY;

        return true;
      }
    }
  }

  return false;
}

int clamp(int x, int a, int b)
{
  return x < a ? a : (x > b ? b : x);
}

byte generateRandomNumber(byte maxValue)
{
    randomCounter += arduboy.lastFrameStart;
    int nr = randomCounter;
    nr *= maxValue * 10;
    nr /= 2560;
     
    return nr;
}

void updateScene()
{
  camX = clamp(player.x - 56, (player.currentMap == 0)?0:((player.currentMap - 1) * 128), (player.currentMap == 0)?(2048 - 128):((player.currentMap - 1) * 128));
  camY = clamp(player.y - 24, (player.currentMap == 0)?0:2048, (player.currentMap == 0)?(2048 - 64):2048);
  
  for(byte i = 0; i < TRIGGERAMOUNT; i++)
  {
    if(triggers[i].map == player.currentMap && (triggers[i].options & 0b00000001))
    {
      // TODO: remove.rework hard coded chest in house
      if(i == 2 && !player.tags[0]) continue;
           
      bool result = false;

      if(player.direction == DIR_UP && ((player.x + 8) / 16) == triggers[i].x && ((player.y - 1) / 16) == triggers[i].y) result = true;
      else if(player.direction == DIR_DOWN && ((player.x + 8) / 16) == triggers[i].x && ((player.y + 16) / 16) == triggers[i].y) result = true;
      else if(player.direction == DIR_LEFT && ((player.x - 1) / 16) == triggers[i].x && ((player.y + 8) / 16) == triggers[i].y) result = true;
      else if(player.direction == DIR_RIGHT && ((player.x + 16) / 16) == triggers[i].x && ((player.y + 8) / 16) == triggers[i].y) result = true;
      
      if(result)
      {
        if(getButtonDown(B_BUTTON))
        {
          if(triggers[i].type == TRIGGERTYPE_TEXTBOX) showTextbox(triggers[i].value, false);
          else if(triggers[i].type == TRIGGERTYPE_ITEM)
          {
            player.items[triggers[i].value]++;
            generateItemFoundTextbox(triggers[i].value);
            showDynamicTextbox(false);
          }
          
          //if(triggers[i].options & 0b00000010) triggers[i].options ^= 0b00000001;

          if(triggers[i].options & 0b00000010) player.tags[0] = false;
        }
      }
    }
  }

  if(player.currentMap >= 3 && playerSteps > 100)
  {
    if(generateRandomNumber(10) < 7) startBattle();
    playerSteps = 0;
  }

  if(getButtonDown(A_BUTTON)) menuIsVisible = true;
}

void drawScene()
{
  byte x = 0;
  byte y = 0;

  for(int i = 0; i < 6; i++)
  {
    drawBlock(pgm_read_byte(&world[y + (camY / 64)][x + (camX / 64)]), (x + (camX / 64)) * 4, (y + (camY / 64)) * 4);

    x++;

    if(x == 3)
    {
      y++;
      x = 0;
    }
  }

  for(byte i = 0; i < TRIGGERAMOUNT; i++)
  {
    // TODO: remove hardcoded chest in house
    if(triggers[i].map == player.currentMap && /*(triggers[i].options & 0b00000001) &&*/ triggers[i].options & 0b00000100 && player.tags[0])
    {
        //arduboy.fillRect(triggers[i].x * 16, triggers[i].y * 16, 16, 8, BLACK);
        //arduboy.drawBitmap(triggers[i].x * 16, triggers[i].y * 16, tiles[98], 16, 8, WHITE);
    }
  }
}

void drawBlock(byte id, int startX, int startY)
{
  byte x = startX;
  byte y = startY;
  
  for(int i = 0; i < 16; i++)
  {
    byte t = pgm_read_byte(&blocks[id-1][i]);
    arduboy.drawBitmap((x * 16)  - camX, (y * 16) - camY, tiles[t - ((t >= 128)?128:0)], 16, 16, WHITE);

    x++;

    if(x == startX + 4)
    {
      y++;
      x = startX;
    }
  }
}

//------------------------
// TEXT
//------------------------

void showTextbox(byte id, bool showInstantly)
{
  textboxCurrentText = id;
  textboxIsVisible = true;
  textboxCurrentProgress = (showInstantly)?pgm_read_byte(&texts[textboxCurrentText][0]):0;
  textboxIsDynamic = false;
  textboxIsChoice = (pgm_read_byte(&texts[textboxCurrentText][3]) & 1)?true:false;
  textboxCurrentChoice = 0;
}

void showDynamicTextbox(bool showInstantly)
{
  textboxIsVisible = true;
  textboxCurrentProgress = (showInstantly)?dynamicTextbox[0]:0;
  textboxIsDynamic = true;
  textboxIsChoice = dynamicTextbox[3];
  textboxCurrentChoice = 0;
}

void doTextbox()
{
  arduboy.fillRect(0, 46, 128, 18, BLACK);
  
  for(byte i = 0; i < textboxCurrentProgress; i++)
  {
    if(textboxIsDynamic)
    {
      if(dynamicTextbox[i + 4] != NONE) arduboy.drawBitmap(4 + (i * 6) - ((i > dynamicTextbox[1])?((dynamicTextbox[1] + 1) * 6):0), 50 + ((i > dynamicTextbox[1])?6:0), font[dynamicTextbox[i + 4]], 5, 5, WHITE);
    }
    else
    {
      if((pgm_read_byte(&texts[textboxCurrentText][i + 4])) != NONE) arduboy.drawBitmap(4 + (i * 6) - ((i > pgm_read_byte(&texts[textboxCurrentText][1]))?((pgm_read_byte(&texts[textboxCurrentText][1]) + 1) * 6):0), 50 + ((i > pgm_read_byte(&texts[textboxCurrentText][1]))?6:0), font[pgm_read_byte(&texts[textboxCurrentText][i + 4])], 5, 5, WHITE);
    }
  }

  byte textLength = (textboxIsDynamic)?dynamicTextbox[0]:pgm_read_byte(&texts[textboxCurrentText][0]);
  if(textboxCurrentProgress < textLength) textboxCurrentProgress++;
  else textboxIsComplete = true;

  if(textboxIsComplete)
  {
    if(textboxIsChoice)
    {
      arduboy.fillRect(96, 28, 32, 18, BLACK);

      drawText(YesNoLabels, 106, 32, WHITE, ALIGN_LEFT);

      arduboy.drawBitmap(100, 32 + (textboxCurrentChoice * 6), font[43], 5, 5, WHITE);

      if(getButtonDown(UP_BUTTON) || getButtonDown(DOWN_BUTTON)) textboxCurrentChoice = (textboxCurrentChoice == 1)?0:1;
    }

    if(getButtonDown(A_BUTTON))
    {
      if(textboxIsChoice)
      {
        textboxIsComplete = false;
        textboxIsVisible = false;
      }
    }
    
    if(getButtonDown(B_BUTTON))
    {
      textboxIsComplete = false;

      if((textboxIsChoice && textboxCurrentChoice == 0) || !textboxIsChoice)
      {
        byte nextUp = (textboxIsDynamic)?dynamicTextbox[2]:pgm_read_byte(&texts[textboxCurrentText][2]);

        if(nextUp == NONE) textboxIsVisible = false;
        else if(nextUp == 128) //Sleep
        {
          nextState = STATE_GAMEPLAY;
          state = STATE_TRANSITION;
          
          player.healthCurrent = player.healthTotal;
          
          textboxIsVisible = false;
        }
        else if(nextUp == 129 || nextUp == 130) //Shop
        {
          state = STATE_SHOP;
          shopState = (nextUp == 129)?SHOPSTATE_BUY:SHOPSTATE_SELL;
          menuItemsChoice = 0;
          
          textboxIsVisible = false;
        }
        else if(nextUp == 131) //Shop
        {
          if(state == STATE_GAMEPLAY)
          {
            if(items[menuItemsLastSelectedItem].type == ITEMTYPE_HEALTH)
            {
              player.items[menuItemsLastSelectedItem]--;

              player.healthCurrent = min(player.healthCurrent + items[menuItemsLastSelectedItem].value, player.healthTotal);
            }
            else if(items[menuItemsLastSelectedItem].type == ITEMTYPE_WEAPON)
            {
              if(menuItemsLastSelectedItem != player.weapon)
              {
                player.weapon = menuItemsLastSelectedItem;
                player.attackAddition = items[menuItemsLastSelectedItem].value;
              }
              else
              {
                player.weapon = NONE;
                player.attackAddition = 0;
              }
            }
            else if(items[menuItemsLastSelectedItem].type == ITEMTYPE_ARMOR)
            {
              if(menuItemsLastSelectedItem != player.armor)
              {
                player.armor = menuItemsLastSelectedItem;
                player.defenseAddition = items[menuItemsLastSelectedItem].value;
              }
              else
              {
                player.armor = NONE;
                player.defenseAddition = 0;
              }
            }
          }
          else if(state == STATE_SHOP)
          {
            if(shopState == SHOPSTATE_BUY)
            {
              player.gold -= items[menuItemsLastSelectedItem].price;
              player.items[menuItemsLastSelectedItem]++;
            }
            else
            {
              player.gold += items[menuItemsLastSelectedItem].price / 2;
              player.items[menuItemsLastSelectedItem]--;
            }
          }
          
          textboxIsVisible = false;
        }
        else if(nextUp == 132) //Save
        {
          save();
          
          textboxIsVisible = false;
        }
        else showTextbox(nextUp, false);
      }
      else textboxIsVisible = false;
    }
  }
}

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
      if(text[i + 1] != NONE) arduboy.drawBitmap(x - ((alignment == ALIGN_RIGHT)?((text[0] - 1) * 6):0) + xOffset, y + yOffset, font[text[i + 1]], 5, 8, color);
      xOffset += 6;
    }
  }
}

void drawNumber(int number, byte x, byte y, byte color, byte alignment)
{
  generateNumber(number);

  drawText(dynamicNumber, x, y, color, alignment);
}

//------------------------
// TEXT GENERATION
//------------------------

void clearDynamicTextbox()
{
  for(int i = 0; i < 44; i++)
  {
    dynamicTextbox[i] = NONE;
  }
}

void generateItemFoundTextbox(byte item)
{
  clearDynamicTextbox();

  memcpy(dynamicTextbox + 4, player.name + 1, player.name[0]);
  memcpy(dynamicTextbox + 4 + player.name[0] + 1, wordFound, 5);
  memcpy(dynamicTextbox + 4 + player.name[0] + 6, items[item].name + 1, items[item].name[0]);
  dynamicTextbox[4 + player.name[0] + 6 + items[item].name[0]] = 38;
  
  dynamicTextbox[0] = player.name[0] + 7 + items[item].name[0];
  dynamicTextbox[1] = player.name[0] + 5;
  dynamicTextbox[2] = NONE;
  dynamicTextbox[3] = 0;
}

void generateBuySellTextbox(byte item)
{
  clearDynamicTextbox();

  byte wordLength = (shopState == SHOPSTATE_BUY)?10:11;

  memcpy(dynamicTextbox + 4, (shopState == SHOPSTATE_BUY)?wordBuy:wordSell, wordLength);
  
  generateNumber(items[item].price / ((shopState == SHOPSTATE_BUY)?1:2));
  
  dynamicTextbox[4 + wordLength] = 47;
  memcpy(dynamicTextbox + 5 + wordLength, dynamicNumber + 1, dynamicNumber[0]);

  dynamicTextbox[5 + wordLength + dynamicNumber[0]] = 39;
  
  dynamicTextbox[0] = wordLength + 2 + dynamicNumber[0];
  dynamicTextbox[1] = NONE;
  dynamicTextbox[2] = 131;
  dynamicTextbox[3] = 1;
}

void generateItemDescriptionText(byte item)
{
  generateNumber(items[item].value);

  if(items[item].type == ITEMTYPE_HEALTH)
  {
    memcpy(dynamicText + 1, wordHealth0, 9);

    memcpy(dynamicText + 10, dynamicNumber + 1, dynamicNumber[0]);
    memcpy(dynamicText + 10 + dynamicNumber[0], wordHealth1, 2);

    dynamicText[0] = 11 + dynamicNumber[0];
  }
  else if(items[item].type == ITEMTYPE_WEAPON || items[item].type == ITEMTYPE_ARMOR)
  {
    memcpy(dynamicText + 1, ((items[item].type == ITEMTYPE_WEAPON)?wordWeapon0:wordArmor0), ((items[item].type == ITEMTYPE_WEAPON)?9:8));
    
    memcpy(dynamicText + ((items[item].type == ITEMTYPE_WEAPON)?10:9), dynamicNumber + 1, dynamicNumber[0]);
    memcpy(dynamicText + ((items[item].type == ITEMTYPE_WEAPON)?10:9) + dynamicNumber[0], wordWeaponArmor1, 3);
    
    dynamicText[0] = ((items[item].type == ITEMTYPE_WEAPON)?11:10) + dynamicNumber[0];
  }
}

void generateGoldText()
{
  generateNumber(player.gold);
  dynamicText[1] = 47;

  memcpy(dynamicText + 2, dynamicNumber + 1, dynamicNumber[0]);
  
  dynamicText[0] = dynamicNumber[0] + 1;
}

void generateBattleGainTextbox(int exp, int gold)
{
  clearDynamicTextbox();

  memcpy(dynamicTextbox + 4, wordGainedExp0, 6);
  
  generateNumber(exp);
  
  memcpy(dynamicTextbox + 11, dynamicNumber + 1, dynamicNumber[0]);
  memcpy(dynamicTextbox + 12 + dynamicNumber[0], wordGainedExp1, 4);

  dynamicTextbox[1] = 12 + dynamicNumber[0];

  memcpy(dynamicTextbox + 5 + dynamicTextbox[1], wordFound, 5);
  dynamicTextbox[11 + dynamicTextbox[1]] = 47;

  generateNumber(gold);

  memcpy(dynamicTextbox + 12 + dynamicTextbox[1], dynamicNumber + 1, dynamicNumber[0]);
  dynamicTextbox[12 + dynamicTextbox[1] + dynamicNumber[0]] = 38;

  dynamicTextbox[0] = dynamicTextbox[1] + 12 + dynamicNumber[0];
  dynamicTextbox[2] = NONE;
  dynamicTextbox[3] = 0;
}

void generateNumber(int number)
{
  int nr = number;

  unsigned char array[8];
  byte counter = 8;
  do
  {
    byte digit = nr % 10;
    array[counter-1] = digit + 26;
    counter--;
    nr /= 10;
  }
  while(nr > 0);

  memcpy(dynamicNumber + 1, array + counter, 8 - counter);
  dynamicNumber[0] = 8 - counter;
}

//------------------------
// MENUS
//------------------------

void doEnterName()
{
  arduboy.fillRect(0, 10, 128, 54, WHITE);
  drawText(labelYourName, 4, 2, WHITE, ALIGN_LEFT);

  byte x = 16;
  byte y = 26;
  for(byte i = 0; i < 27; i++)
  {
    arduboy.drawBitmap(x, y, font[(i < 26)?i:49], 5, 5, BLACK);

    x += 12;

    if(x == 124)
    {
      y += 12;
      x = 16;
    }
  }

  if(getButtonDown(UP_BUTTON)) cursorY += (cursorY > 0)?-1:2;
  else if(getButtonDown(DOWN_BUTTON)) cursorY += (cursorY < 2)?1:-2;
  else if(getButtonDown(LEFT_BUTTON)) cursorX += (cursorX > 0)?-1:8;
  else if(getButtonDown(RIGHT_BUTTON)) cursorX += (cursorX < 8)?1:-8;
  else if(getButtonDown(B_BUTTON))
  {
    if(cursorX + (cursorY * 9) == 26)
    {
      if(currentLetter == 0)
      {
        player.name[0] = 4;
        player.name[1] = 11;
        player.name[2] = 4;
        player.name[3] = 13;
        player.name[4] = 0;
      }
      state = STATE_TRANSITION;
      nextState = STATE_GAMEPLAY;

      currentLetter = 0;
      cursorX = 0;
      cursorY = 0;

      return;
    }
    else
    {
      player.name[currentLetter + 1] = cursorX + (cursorY * 9);
      currentLetter = min(currentLetter + 1, 5);
    }
  }
  else if(getButtonDown(A_BUTTON))
  {
    if(currentLetter > 0)
    {
      currentLetter--;
      player.name[currentLetter + 1] = NONE;
    }
  }
  player.name[0] = currentLetter;

  arduboy.drawBitmap(10 + (cursorX * 12), 26 + (cursorY * 12), font[43], 5, 5, BLACK);

  for(byte i = currentLetter; i < 5; i++)
  {
    arduboy.drawBitmap(46 + (i * 6), 14, font[48], 5, 5, BLACK);
  }
  
  drawText(player.name, 46, 14, BLACK, ALIGN_LEFT);
}

void doMenu()
{
  if(!menuIsSpecific)
  {
    // Draw
    arduboy.fillRect(84, 0, 64, 64, BLACK);

    for(byte i = 0; i < 3; i++)
    {
      drawText(menuLabels[i], 94, 2 + (i * 12), WHITE, ALIGN_LEFT);
    }
    
    arduboy.drawBitmap(88, 2 + (menuMainChoice * 12), font[43], 5, 5, WHITE);
  
    // Update
    if(textboxIsVisible) return;
    
    if(getButtonDown(UP_BUTTON)) menuMainChoice = max(menuMainChoice - 1, 0);
    if(getButtonDown(DOWN_BUTTON)) menuMainChoice = min(menuMainChoice + 1, 2);
    
    if(getButtonDown(A_BUTTON)) menuIsVisible = false;
    
    if(getButtonDown(B_BUTTON))
    {
      if(menuMainChoice == 2)
      {
        showTextbox(8, false);
        menuIsVisible = false;
      }
      else
      {
        menuItemsChoice = 0;
        menuIsSpecific = true;
      }
    }
  }
  else
  {    
    if(getButtonDown(A_BUTTON) && !textboxIsVisible) menuIsSpecific = false;
    
    arduboy.fillRect(0, 10, 128, (menuMainChoice == 1)?54:36, WHITE);

    drawText(menuLabels[menuMainChoice], 4, 2, WHITE, ALIGN_LEFT);

    if(menuMainChoice == 0) // ITEMS
    {
      doItemList();
    }
    else if(menuMainChoice == 1) // STATS
    {
      drawText(statsLabels0, 4, 14, BLACK, ALIGN_LEFT);
      drawText(statsLabels1, 88, 14, BLACK, ALIGN_LEFT);
      drawText(player.name, 34, 14, BLACK, ALIGN_LEFT);
      
      drawNumber(player.gold, 46, 20, BLACK, ALIGN_LEFT);  
      drawNumber(player.level, 118, 14, BLACK, ALIGN_RIGHT);
      drawNumber(player.attack + player.attackAddition, 118, 26, BLACK, ALIGN_RIGHT);
      drawNumber(player.defense + player.defenseAddition, 118, 32, BLACK, ALIGN_RIGHT);
      drawNumber(player.speed + player.speedAddition, 118, 38, BLACK, ALIGN_RIGHT);

      drawHealth(4, 38, BLACK);
      
      drawNumber(player.experience, 4, 56, BLACK, ALIGN_LEFT);
      arduboy.drawBitmap(4 + (dynamicNumber[0] * 6), 56, font[42], 5, 5, BLACK);  
      drawNumber(player.experienceForNextLevel, 10 + (dynamicNumber[0] * 6), 56, BLACK, ALIGN_LEFT);
    }
  }
}

void doItemList()
{
  // Get a list of items that the player or shop has
  byte itemCounter = 0;
  byte itemArray[ITEMAMOUNT];

  for(byte i = 0; i < ITEMAMOUNT; i++)
  {
    if(state == STATE_GAMEPLAY || (state == STATE_SHOP && shopState == SHOPSTATE_SELL))
    {
      if(state == STATE_SHOP && shopState == SHOPSTATE_SELL)
      {
        if(i == player.weapon || i == player.armor) continue;
      }
      if(player.items[i] == 0) continue;
    }
    else
    {
      if(!((shopItems >> i) & 1)) continue;
    }

    itemArray[itemCounter] = i;
    itemCounter++;
  }

  // Draw list of 5 items
  for(byte i = 0; i < 5; i++)
  {
    byte yPos = 14 + (i * 6);

    if(i + menuItemsListOffset == itemCounter) break;
     
    drawText(items[itemArray[i + menuItemsListOffset]].name, 10, yPos, BLACK, ALIGN_LEFT);
    if(itemArray[i + menuItemsListOffset] == player.weapon || itemArray[i + menuItemsListOffset] == player.armor) arduboy.drawBitmap(10 + (items[itemArray[i + menuItemsListOffset]].name[0] * 6), yPos, font[46], 5, 5, BLACK);

    drawNumber((state == STATE_GAMEPLAY || (state == STATE_SHOP && shopState == SHOPSTATE_SELL))?player.items[itemArray[i + menuItemsListOffset]]:items[itemArray[i + menuItemsListOffset]].price, 112, yPos, BLACK, ALIGN_RIGHT);
    arduboy.drawBitmap((state == STATE_GAMEPLAY || (state == STATE_SHOP && shopState == SHOPSTATE_SELL))?100:(112 - (dynamicNumber[0] * 6)), yPos, font[(state == STATE_GAMEPLAY || (state == STATE_SHOP && shopState == SHOPSTATE_SELL))?23:47], 5, 5, BLACK);
  }

  if(itemCounter == 0) drawText(itemNone, 40, 26, BLACK, ALIGN_LEFT);
  else 
  {
    arduboy.drawBitmap(4, 14 + (menuItemsChoice * 6) - (menuItemsListOffset * 6), font[43], 5, 5, BLACK);
   
    generateItemDescriptionText(itemArray[menuItemsChoice]);
    drawText(dynamicText, 4, 50, WHITE, ALIGN_LEFT);

    // Draw up and or down arrow if scrolling up is possible
    if(menuItemsListOffset > 0) arduboy.drawBitmap(118, 14, font[44], 5, 5, BLACK);
    if(menuItemsListOffset < itemCounter - 5) arduboy.drawBitmap(118, 38, font[45], 5, 5, BLACK);

    if(textboxIsVisible) return;
  
    if(getButtonDown(UP_BUTTON)) 
    {
      menuItemsChoice = max(menuItemsChoice - 1, 0);
      if(menuItemsChoice - menuItemsListOffset < 0) menuItemsListOffset--;
    }
    else if(getButtonDown(DOWN_BUTTON))
    {
      menuItemsChoice = min(menuItemsChoice + 1, itemCounter - 1);
      if(menuItemsChoice - menuItemsListOffset > 4) menuItemsListOffset++;
    }

    if(menuItemsOldAmount != itemCounter)
    {
      menuItemsChoice = min(menuItemsChoice, itemCounter - 1);
      menuItemsListOffset = max(menuItemsChoice - 4, 0);
    }
    
    if(getButtonDown(B_BUTTON))
    {
      if(state == STATE_GAMEPLAY)
      {
        if(items[itemArray[menuItemsChoice]].type != ITEMTYPE_OTHER) showTextbox(9 + ((items[itemArray[menuItemsChoice]].type > 0)?1:0) + ((itemArray[menuItemsChoice] == player.weapon || itemArray[menuItemsChoice] == player.armor)?1:0), true);
      }
      else
      {
        if(shopState == SHOPSTATE_SELL || items[itemArray[menuItemsChoice]].price <= player.gold)
        {
          generateBuySellTextbox(itemArray[menuItemsChoice]);
          showDynamicTextbox(true);
        }
      }
    }
  }

  menuItemsOldAmount = itemCounter;
  menuItemsLastSelectedItem = itemArray[menuItemsChoice];
}

void drawHealth(byte x, byte y, byte color)
{
  drawNumber(player.healthCurrent, x, y, color, ALIGN_LEFT);
  arduboy.drawBitmap(x + (dynamicNumber[0] * 6), y, font[42], 5, 5, color);  
  drawNumber(player.healthTotal, x + 6 + (dynamicNumber[0] * 6), y, color, ALIGN_LEFT);
}

//------------------------
// BATTLE
//------------------------

void startBattle()
{
  battleStartEffectCounter = 40;
  battleState = BATTLESTATE_ACTIONCHOICE;
  currentActionChoice = 0;
  currentEnemyChoice = 0;

  currentBattleFormation = generateRandomNumber(BATTLEFORMATIONAMOUNT);
  currentEnemyAmount = pgm_read_byte(&battleFormations[currentBattleFormation][0]);
  
  for(byte i = 0; i < 4; i++)
  {
    currentEnemyHealth[i] = (i < currentEnemyAmount)?enemies[pgm_read_byte(&battleFormations[currentBattleFormation][i + 1])].health:0;
    currentEnemies[i] = (i < currentEnemyAmount)?enemies[pgm_read_byte(&battleFormations[currentBattleFormation][i + 1])].id:0;
  }
}

void drawBattle()
{
  arduboy.fillRect(0, 10, 128, 36, WHITE);

  for(int i = 0; i < currentEnemyAmount; i++)
  {
    byte xPos = ((128 - (currentEnemyAmount * 16) - ((currentEnemyAmount - 1) * 4)) / 2) + (i * 20);
    if(currentEnemyHealth[i] != 0)
    {
      if(battleState == BATTLESTATE_ENEMYCHOICE && i == currentEnemyChoice) arduboy.drawBitmap(xPos + 5, 20, font[45], 5, 5, BLACK);
      
      if(battleState == BATTLESTATE_ENEMIESDAMAGING && i == currentEnemyChoice && !battleDamageEffectToggle) continue;
      else arduboy.drawBitmap(xPos, (battleState == BATTLESTATE_PLAYERDAMAGING && i == currentEnemyTurn)?22:26, enemyBitmaps[currentEnemies[i]], 16, 16, BLACK);
    }
  }

  arduboy.drawBitmap(battleChoicePositions[currentActionChoice], 50, font[43], 5, 5, WHITE);
  drawText(battleChoices, 10, 50, WHITE, ALIGN_LEFT);
  
  drawText(labelHealth, 4, 2, WHITE, ALIGN_LEFT);
  drawHealth(22, 2, WHITE);

  if(battleState == BATTLESTATE_ENEMYCHOICE)
  {
    drawText(enemyNames[currentEnemies[currentEnemyChoice]], 4, 14, BLACK, ALIGN_LEFT);
  }
}

void updateBattle()
{
  // Enemy damage blinking effect
  if(battleState == BATTLESTATE_ENEMIESDAMAGING)
  {
    if(battleDamageEffectCounter > 0)
    {
      if(--battleDamageEffectCounter % 2 == 0) battleDamageEffectToggle = !battleDamageEffectToggle;
    }
    else
    {
      battleDamageEffectToggle = true;
      if(battleState == BATTLESTATE_ENEMIESDAMAGING) battleState = BATTLESTATE_ENEMIESATTACKING;
    }
  }
  
  if(textboxIsVisible) return;
  
  if(battleState == BATTLESTATE_ACTIONCHOICE)
  {
    if(getButtonDown(LEFT_BUTTON)) currentActionChoice = clamp(currentActionChoice - 1, 0, 2);
    else if(getButtonDown(RIGHT_BUTTON)) currentActionChoice = clamp(currentActionChoice + 1, 0, 2);

    if(getButtonDown(B_BUTTON))
    {
      switch(currentActionChoice)
      {
        case 0: // Fight
          battleState = BATTLESTATE_ENEMYCHOICE;
        break;
  
        case 1: // Items
          showTextbox(12, false);
        break;
        
        case 2: // Run
          if(true)
          {
            showTextbox(5, false);
            battleState = BATTLESTATE_END;
          }
          else 
          {
            battleState = BATTLESTATE_ENEMIESATTACKING;
          }
        break;
      }
    }
  }
  else if(battleState == BATTLESTATE_ENEMYCHOICE)
  {
    int offset = 0;
    byte oldChoice = currentEnemyChoice;

    if(currentEnemyHealth[currentEnemyChoice] <= 0)
    {
      for(byte i = 0; i < 4; i++)
      {
        if(currentEnemyHealth[i] > 0)
        {
          currentEnemyChoice = i;
          break;
        }
      }
    }
    
    if(getButtonDown(LEFT_BUTTON))
    {
      currentEnemyChoice = clamp(currentEnemyChoice - 1, 0, currentEnemyAmount - 1);

      while(currentEnemyHealth[currentEnemyChoice] <= 0 && currentEnemyChoice >= 0)
      {
        if(currentEnemyChoice == 0)
        {
          currentEnemyChoice = oldChoice;
          break;
        }
        else currentEnemyChoice--;
      }
    }
    else if(getButtonDown(RIGHT_BUTTON))
    {
      currentEnemyChoice = clamp(currentEnemyChoice + 1, 0, currentEnemyAmount - 1);

      while(currentEnemyHealth[currentEnemyChoice] <= 0 && currentEnemyChoice <= currentEnemyAmount - 1)
      {
        if(currentEnemyChoice == currentEnemyAmount - 1)
        {
          currentEnemyChoice = oldChoice;
          break;
        }
        else currentEnemyChoice++;
      }
    }

    if(getButtonDown(B_BUTTON))
    {
      generateAttackText(true);
      showDynamicTextbox(false);

      battleState = BATTLESTATE_PLAYERATTACKING;
    }
    if(getButtonDown(A_BUTTON)) battleState = BATTLESTATE_ACTIONCHOICE;
  }
  else if(battleState == BATTLESTATE_PLAYERATTACKING)
  {
    doDamageStuff(true);
    showDynamicTextbox(false);
    battleDamageEffectCounter = 20;

    battleState = BATTLESTATE_ENEMIESDAMAGING;
  }
  else if(battleState == BATTLESTATE_ENEMIESATTACKING)
  {
    // TODO: Player stuff shouldn't be here, it's kind of messy!
    if(player.healthCurrent == 0)
    {
      nextState = STATE_GAMEOVER;
      state = STATE_TRANSITION;

      resetPlayer();

      return;
    }
    
    if(currentEnemyHealth[currentEnemyChoice] == -1)
    {
      currentEnemyHealth[currentEnemyChoice] = 0;
      generateFaintText();
      showDynamicTextbox(false);
    }
    else if(currentEnemyHealth[0] == 0 && currentEnemyHealth[1] == 0 && currentEnemyHealth[2] == 0 && currentEnemyHealth[3] == 0)
    {
      showTextbox(6, false);
      battleState = BATTLESTATE_WON;
    }
    else
    {
      while(currentEnemyHealth[currentEnemyTurn] == 0)
      {
        currentEnemyTurn++;
        if(currentEnemyTurn >= currentEnemyAmount) break;
      }

      if(currentEnemyTurn < currentEnemyAmount)
      {
        generateAttackText(false);
        showDynamicTextbox(false);
        
        battleState = BATTLESTATE_PLAYERDAMAGING;
      }
      else
      {
        battleState = BATTLESTATE_ACTIONCHOICE;
        currentEnemyTurn = 0;
      }
    }
  }
  else if(battleState == BATTLESTATE_PLAYERDAMAGING)
  {
    doDamageStuff(false);
    showDynamicTextbox(false);

    currentEnemyTurn++;
    battleState = BATTLESTATE_ENEMIESATTACKING;
  }
  else if(battleState == BATTLESTATE_WON)
  {
    int exp = 0;
    int gold = 0;
    for(byte i = 0; i < currentEnemyAmount; i++)
    {
      exp += enemies[currentEnemies[i]].exp;
      gold += enemies[currentEnemies[i]].gold;
    }

    player.experience += exp;
    player.gold += gold;
    
    generateBattleGainTextbox(exp, gold);
    showDynamicTextbox(false);

    battleState = BATTLESTATE_END;
  }
  else if(battleState == BATTLESTATE_END)
  {
    if(player.experience >= player.experienceForNextLevel)
    {
      doLevelUp();

      showTextbox(13, false);
    }
    else
    {
      state = STATE_TRANSITION;
      nextState = STATE_GAMEPLAY;
    }
  }

  if(!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)) changedChoice = false;
}

void doDamageStuff(bool AttackerIsPlayer)
{
  clearDynamicTextbox();

  byte nameLength = (AttackerIsPlayer)?enemyNames[currentEnemies[currentEnemyChoice]][0]:player.name[0];

  // Put player or enemy name in dynamic text array
  memcpy(dynamicTextbox + 4, ((AttackerIsPlayer)?enemyNames[currentEnemies[currentEnemyChoice]]:player.name) + 1, nameLength);

  // Put "takes" in dynamic text array
  memcpy(dynamicTextbox + 4 + nameLength + 1, wordTakes, 5);
  
  // Set newline and offset
  dynamicTextbox[1] = nameLength + 1 + 5;

  // Calculate attack value
  int attackValue;
  if(AttackerIsPlayer)
  {
    attackValue = max(player.attack + player.attackAddition - enemies[currentEnemies[currentEnemyChoice]].defense, 0);
    currentEnemyHealth[currentEnemyChoice] = currentEnemyHealth[currentEnemyChoice] - attackValue;
    if(currentEnemyHealth[currentEnemyChoice] <= 0) currentEnemyHealth[currentEnemyChoice] = -1;
  }
  else
  {
    attackValue = max(enemies[currentEnemies[currentEnemyTurn]].attack - (player.defense + player.defenseAddition), 1);
    player.healthCurrent = max(player.healthCurrent - attackValue, 0);
  }

  // Convert attack value to char array
  unsigned char array[3];
  byte counter = 3;
  do
  {
    byte digit = attackValue % 10;
    array[counter-1] = digit + 26;
    counter--;
    attackValue /= 10;
  }
  while(attackValue > 0);

  // Put attack value char array in dynamic text array
  memcpy(dynamicTextbox + 4 + nameLength + 1 + 5 + 1, array + counter, 3 - counter);

  // Put "damage!" in dynamic text array
  memcpy(dynamicTextbox + 4 + nameLength + 1 + 5 + 1 + 3 - counter + 1, wordDamage, 7);

  // Set dynamic text length
  dynamicTextbox[0] = nameLength + 1 + 5 + 1 + 3 - counter + 1 + 7;

  dynamicTextbox[3] = false;
}

void generateAttackText(bool DamagedIsPlayer)
{
  clearDynamicTextbox();

  // Get length of player or enemy name
  byte nameLength = (DamagedIsPlayer)?player.name[0]:enemyNames[currentEnemies[currentEnemyTurn]][0];

  // Put player or enemy name in dynamic text array
  memcpy(dynamicTextbox + 4, ((DamagedIsPlayer)?player.name:enemyNames[currentEnemies[currentEnemyTurn]]) + 1, nameLength);

  // Put "takes" in dynamic text array
  memcpy(dynamicTextbox + 4 + nameLength + 1, wordAttacks, 8);
  
  // Set newline and offset
  dynamicTextbox[1] = nameLength + 1 + 8;

  // Set dynamic text length
  dynamicTextbox[0] = nameLength + 1 + 8;

  dynamicTextbox[3] = 0;
}

void generateFaintText()
{
  clearDynamicTextbox();

  byte nameLength = enemyNames[currentEnemies[currentEnemyChoice]][0];

  memcpy(dynamicTextbox + 4, enemyNames[currentEnemies[currentEnemyChoice]] + 1, nameLength);
  memcpy(dynamicTextbox + 4 + nameLength + 1, wordFainted, 8);

  dynamicTextbox[0] = nameLength + 9;
  dynamicTextbox[3] = false;
}

void doLevelUp()
{
  player.experience -= player.experienceForNextLevel;
  player.experienceForNextLevel *= 2;

  player.level++;
  player.healthTotal += 5;
  player.healthCurrent = player.healthTotal;
  player.attack++;
  player.defense++;
  player.speed++;
}

//------------------------
// PROGRESS
//------------------------
byte saveKey = 121;

void save()
{
  EEPROM.put(0, saveKey);
  EEPROM.put(1, player);
}

bool checkLoad()
{
  byte nr;
  EEPROM.get(0, nr);
  
  return (nr == saveKey);
}

void load()
{
    EEPROM.get(1, player);
}

//------------------------
// INPUT
//------------------------
bool getButtonDown(byte button)
{
  if(arduboy.pressed(button))
  {
    if(buttons & button) return false;
    else buttons |= button;
    return true;
  }
  else
  {
    if(buttons & button) buttons ^= button;
    return false;
  }
}

#endif
