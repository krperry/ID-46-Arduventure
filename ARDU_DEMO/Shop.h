#define SHOPSTATE_BUY 0
#define SHOPSTATE_SELL 1

byte shopState = SHOPSTATE_BUY;

int shopItems = 0b0000000000111111;

const unsigned char labelShopBuy[] = {8, 18,7,14,15,53,1,20,24};
const unsigned char labelShopSell[] = {9, 18,7,14,15,53,18,4,11,11};
