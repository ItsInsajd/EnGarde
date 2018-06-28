#include <Gamebuino-Meta.h>
#include "Character.h"
#include "Constants.h"
#include "World.h"
#include "AStar.h"
#include "Camera.h"

const uint8_t coinGuiBuff[] = {8, 8, 1, 0, 0, 0x02, 1, 0x22, 0x22,0x22, 0x22,0x22, 0x2a,0x92, 0x22,0x22, 0xaa,0xa9, 0x22,0x22, 0xaa,0xa9, 0x22,0x22, 0xaa,0xa9, 0x22,0x22, 0x2a,0x92, 0x22,0x22, 0x22,0x22, 0x22,0x22, 0x22,0x22, 0x22};
Image coinGui = Image(coinGuiBuff);
const uint8_t coinBuff[] = {8, 8, 5, 0, 3, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe7,0xfe, 0xee,0xee, 0xaa,0x7f, 0xee,0xee, 0xaa,0xaf, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe7,0xfe, 0xee,0xee, 0x77,0x7f, 0xee,0xee, 0xa7,0x7f, 0xee,0xee, 0xaa,0x7f, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0x7a,0xa9, 0xee,0xee, 0x77,0xa9, 0xee,0xee, 0x77,0x79, 0xee,0xee, 0xe7,0xfe, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xea,0x9e, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0xaa,0xa9, 0xee,0xee, 0x7a,0xa9, 0xee,0xee, 0xe7,0x9e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee};
Image coin = Image(coinBuff);
const uint8_t heartGuiData[] = {8, 8, 1, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0x8e,0x82, 0xee,0xe8, 0x88,0x88, 0x2e,0xe8, 0x88,0x88, 0x2e,0xee, 0x88,0x82, 0xee,0xee, 0xe8,0x2e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee};
Image heartGui = Image(heartGuiData);
const uint8_t heartEmptyGuiData[] = {8, 8, 1, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0x7e,0x76, 0xee,0xe7, 0xe7,0xe7, 0x6e,0xe7, 0xee,0xe7, 0x6e,0xee, 0x7e,0x76, 0xee,0xee, 0xe7,0x6e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee};
Image heartEmptyGui = Image(heartEmptyGuiData);
const uint8_t heartData[] = {8, 8, 5, 0, 3, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0x8e,0x82, 0xee,0xe8, 0x88,0x88, 0x2e,0xe8, 0x88,0x88, 0x2e,0xee, 0x88,0x82, 0xee,0xee, 0xe8,0x2e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x8e,0x76, 0xee,0xe8, 0x88,0x77, 0x6e,0xe8, 0x88,0x87, 0x6e,0xee, 0x88,0x82, 0xee,0xee, 0xe8,0x2e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x7e,0x76, 0xee,0xe8, 0x77,0x77, 0x6e,0xe8, 0x87,0x77, 0x6e,0xee, 0x88,0x76, 0xee,0xee, 0xe8,0x2e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x7e,0x82, 0xee,0xe7, 0x77,0x88, 0x2e,0xe7, 0x77,0x78, 0x2e,0xee, 0x77,0x76, 0xee,0xee, 0xe7,0x6e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x8e,0x82, 0xee,0xe7, 0x88,0x88, 0x2e,0xe7, 0x78,0x88, 0x2e,0xee, 0x77,0x82, 0xee,0xee, 0xe7,0x6e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee};
Image heart = Image(heartData);
const uint8_t slashBuff[] = {8, 8, 4, 0, 1, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0x7e,0xee, 0xee,0xee, 0xe7,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0x7e,0xee, 0xee,0xee, 0xe7,0xee, 0xee,0xee, 0xee,0x7e, 0xee,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe7,0xee, 0xee,0xee, 0xee,0x7e, 0xee,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0x7e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0x7e, 0xee,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0x7e,0xee, 0xee,0xee, 0xee};
Image slash = Image(slashBuff);
const uint8_t bloodSlashBuff[] = {8, 8, 4, 0, 1, 0x0E, 1, 0xee, 0xe8,0xee, 0xee,0xe8, 0xee,0x7e, 0xee,0xee, 0x8e,0xee, 0xee,0x8e, 0xe7,0xee, 0xee,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe8,0xee, 0xee,0xee, 0xee,0x8e, 0xee,0xee, 0x8e,0xe8, 0xee,0x8e, 0xe8,0xee, 0x7e,0xe8, 0xee,0x8e, 0xee,0xee, 0x8e,0xe7, 0xee,0xee, 0xe7,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0x8e, 0xee,0xee, 0xee,0xe8, 0xee,0xee, 0xe8,0xee, 0x8e,0xe8, 0xee,0x8e, 0xe7,0xee, 0x8e,0xe8, 0xee,0xee, 0xe8,0xee, 0x8e,0xee, 0xee,0x7e, 0xe7,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x8e,0xee, 0xee,0xee, 0xe8,0xee, 0xee,0xe8, 0xee,0xee, 0xe8,0xee, 0x8e,0xee, 0xee,0x8e, 0xe8};
Image bloodSlash = Image(bloodSlashBuff);
const uint8_t chestBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xea, 0x88,0x88, 0xae,0xea, 0x88,0x88, 0xae,0xea, 0xaa,0xaa, 0xae,0xe9, 0x29,0x92, 0x9e,0xe9, 0x22,0x22, 0x9e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xea, 0xaa,0xaa, 0xae,0xea, 0x55,0x55, 0xae,0xea, 0xaa,0xaa, 0xae,0xe9, 0x22,0x22, 0x9e,0xe9, 0x22,0x22, 0x9e};
Image chest = Image(chestBuff);
const byte playerSpriteRightBuff[] = {8, 10, 2, 0, 2, 0x0E, 1, 0xee, 0x77,0x77, 0xee,0xee, 0x70,0x70, 0xee,0xec, 0x77,0x77, 0xee,0xcc, 0xd7,0x7e, 0xe0,0xcd, 0x1d,0xde, 0x0e,0xec, 0xd1,0x00, 0xee,0xec, 0xdd,0xde, 0xee,0xee, 0xde,0xde, 0xee,0xee, 0x1e,0x1e, 0xee,0xee, 0x0e,0x0e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x77, 0xee,0xee, 0x70,0x70, 0xee,0xec, 0x77,0x77, 0xee,0xcc, 0xd7,0x7e, 0xe0,0xcd, 0x1d,0xde, 0x0e,0xec, 0xd1,0x00, 0xee,0xec, 0xdd,0xde, 0xee,0xee, 0x1d,0x1e, 0xee,0xee, 0x0e,0x0e, 0xee};
Image playerSpriteRight = Image(playerSpriteRightBuff);
const uint8_t playerSpriteLeftBuff[] = {8, 10, 2, 0, 2, 0x0E, 1, 0xee, 0x77,0x77, 0xee,0xee, 0x07,0x07, 0xee,0xee, 0x77,0x77, 0xce,0x0e, 0xe7,0x7d, 0xcc,0xe0, 0xed,0xd1, 0xdc,0xee, 0x00,0x1d, 0xce,0xee, 0xed,0xdd, 0xce,0xee, 0xed,0xed, 0xee,0xee, 0xe1,0xe1, 0xee,0xee, 0xe0,0xe0, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x77, 0xee,0xee, 0x07,0x07, 0xee,0xee, 0x77,0x77, 0xce,0x0e, 0xe7,0x7d, 0xcc,0xe0, 0xed,0xd1, 0xdc,0xee, 0x00,0x1d, 0xce,0xee, 0xed,0xdd, 0xce,0xee, 0xe1,0xd1, 0xee,0xee, 0xe0,0xe0, 0xee};
Image playerSpriteLeft = Image(playerSpriteLeftBuff);
const uint8_t enemySprRightBuff[] = {8, 8, 2, 0, 2, 0x0E, 1, 0xee, 0xee,0x99, 0x9e,0xee, 0xe2,0x97, 0x97,0xee, 0x22,0x99, 0x9e,0xee, 0x28,0x28, 0xee,0xee, 0xe2,0x80, 0x00,0xee, 0xe8,0x88, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0x99, 0x9e,0xee, 0xe2,0x97, 0x97,0xee, 0x22,0x99, 0x9e,0xee, 0x28,0x28, 0xee,0xee, 0xe2,0x80, 0x00,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee};
Image enemySprRight = Image(enemySprRightBuff);
const uint8_t enemySprLeftBuff[] = {8, 8, 2, 0, 2, 0x0E, 1, 0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xee, 0x99,0x92, 0x2e,0xee, 0xe8,0x28, 0x2e,0xe0, 0x00,0x82, 0xee,0xee, 0xe8,0x88, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xee, 0x99,0x92, 0x2e,0xee, 0xe8,0x28, 0x2e,0xe0, 0x00,0x82, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee};
Image enemySprLeft = Image(enemySprLeftBuff);
const uint8_t enemyCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe9,0x99, 0xee,0xee, 0x29,0x79, 0x7e,0xe2, 0x89,0x99, 0x2e,0xe8, 0x22,0x82, 0x8e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xe2, 0x99,0x98, 0x2e,0xe8, 0x28,0x22, 0x8e};
Image enemyCorpse = Image(enemyCorpseBuff);
const uint8_t skullRightBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x76,0x77, 0x7e,0xe7, 0x60,0x07, 0x00,0xe6, 0x70,0x07, 0x00,0xee, 0x77,0x70, 0x7e,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee};
Image skullRight = Image(skullRightBuff);
const uint8_t skullLeftBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0xe7, 0x77,0x67, 0x7e,0x00, 0x70,0x06, 0x7e,0x00, 0x70,0x07, 0x6e,0xe7, 0x07,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee};
Image skullLeft = Image(skullLeftBuff);
const uint8_t skullCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x70, 0xee,0xe7, 0x07,0x67, 0x7e,0xe0, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xee, 0x06,0x70, 0x7e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x70, 0xee,0xe7, 0x07,0x67, 0x7e,0xe0, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xee, 0x06,0x70, 0x7e};
Image skullCorpse = Image(skullCorpseBuff);
const uint8_t bloodskullRightBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x78,0x77, 0x7e,0xe7, 0x80,0x07, 0x00,0xe8, 0x70,0x07, 0x00,0xee, 0x78,0x70, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee};
Image bloodskullRight = Image(bloodskullRightBuff);
const uint8_t bloodskullLeftBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0xe7, 0x77,0x87, 0x7e,0x00, 0x70,0x08, 0x7e,0x00, 0x70,0x07, 0x8e,0xee, 0x07,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee};
Image bloodskullLeft = Image(bloodskullLeftBuff);
const uint8_t bloodskullCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x08,0x70, 0xee,0xe8, 0x87,0x87, 0x7e,0xe0, 0x80,0x07, 0x00,0xe7, 0x88,0x07, 0x00,0xee, 0x08,0x70, 0x8e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x80, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x08, 0x0e,0x00, 0x70,0x88, 0x7e,0xe8, 0x07,0x80, 0xee};
Image bloodskullCorpse = Image(bloodskullCorpseBuff);
const uint8_t ghostRightBuff[] = {8, 8, 4, 0, 5, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xde,0xce, 0xce,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xde,0xce, 0xce,0xee, 0xee,0xee, 0xee};
Image ghostRight = Image(ghostRightBuff);
const uint8_t ghostLeftBuff[] = {8, 8, 4, 0, 5, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xce,0xce, 0xde,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0xcc,0xcc, 0xde,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0xcc,0xcc, 0xde,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xce,0xce, 0xde,0xee, 0xee,0xee, 0xee};
Image ghostLeft = Image(ghostLeftBuff);
const uint8_t ghostCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0x7e, 0xee,0xee, 0x7c,0xcc, 0xee,0xe1, 0xcc,0xdc, 0xde,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe7,0xce, 0xee,0xee, 0xcc,0xc7, 0xee,0xed, 0xcd,0xcc, 0x1e};
Image ghostCorpse = Image(ghostCorpseBuff);
const uint8_t ratRightBuff[] = {8, 8, 4, 0, 4, 0x0C, 1, 0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0xcc,0x22, 0xe7,0x27, 0xcc,0xc2, 0x22,0x22, 0x2c,0xcc, 0x22,0x2c, 0xce,0x2c, 0x2e,0xec, 0xcc,0xc2, 0x22,0xec, 0xcc,0xcc, 0x2c,0x2c, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0xcc,0x22, 0xe7,0x27, 0xcc,0xc2, 0x22,0x22, 0x2c,0xcc, 0x2e,0xec, 0xce,0x22, 0x22,0xec, 0xcc,0xcc, 0x2c,0x2c, 0xcc,0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0xcc,0x22, 0xe7,0x27, 0xcc,0xc2, 0x22,0x22, 0x2c,0xcc, 0x22,0x2c, 0xce,0x2c, 0x2e,0xec, 0xcc,0xc2, 0x22,0xec, 0xcc,0xcc, 0x2c,0x2c, 0xcc,0xc2, 0x22,0xcc, 0xcc,0x2e, 0xe2,0x2c, 0xcc,0xc2, 0x72,0x7c, 0xcc,0xcc, 0x22,0x22, 0xcc,0xcc, 0x22,0x2c, 0xec,0x2c, 0x2e,0xec, 0xcc,0xc2, 0x22,0xec, 0xcc,0xcc, 0x2c,0x2c, 0xcc};
Image ratRight = Image(ratRightBuff);
const uint8_t ratLeftBuff[] = {8, 8, 4, 0, 4, 0x0C, 1, 0xcc, 0xcc,0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0x72,0x7e, 0x22,0xc2, 0x22,0x22, 0x2c,0xec, 0xc2,0x22, 0xcc,0xcc, 0xce,0xe2, 0xc2,0xcc, 0xce,0x22, 0x2c,0xcc, 0xc2,0xc2, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0x72,0x7e, 0x22,0xc2, 0x22,0x22, 0x2c,0xec, 0xce,0xe2, 0xcc,0xcc, 0xce,0x22, 0x22,0xcc, 0xc2,0xc2, 0xcc,0xcc, 0xcc,0xc2, 0x2c,0xcc, 0xcc,0x2e, 0xe2,0xcc, 0x72,0x7e, 0x22,0xc2, 0x22,0x22, 0x2c,0xec, 0xc2,0x22, 0xcc,0xcc, 0xce,0xe2, 0xc2,0xcc, 0xce,0x22, 0x2c,0xcc, 0xc2,0xc2, 0xcc,0xcc, 0xcc,0x22, 0x2c,0xcc, 0xc2,0x2e, 0xe2,0xcc, 0xc7,0x27, 0x2c,0xcc, 0x22,0x22, 0xcc,0xce, 0xc2,0x22, 0xcc,0xcc, 0xce,0xe2, 0xc2,0xcc, 0xce,0x22, 0x2c,0xcc, 0xc2,0xc2, 0xcc};
Image ratLeft = Image(ratLeftBuff);
const uint8_t ratCorpseBuff[] = {8, 8, 2, 0, 0, 0x0C, 1, 0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xe2,0x2c, 0xcc,0xc2, 0xe2,0x7c, 0xec,0xc2, 0x72,0x22, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xc2,0x2e, 0xcc,0xce, 0xc7,0x2e, 0x2c,0xcc, 0x22,0x27, 0x2c};
Image ratCorpse = Image(ratCorpseBuff);
const uint8_t necromancerIdleRightData[] = {8, 10, 4, 0, 4, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xe0, 0x00,0xee, 0xee,0xee, 0x07,0xee, 0x9e,0xe0, 0x00,0x09, 0x89,0x00, 0x00,0x0e, 0x9e,0x0e, 0x00,0xe0, 0x5e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0x9e,0xe0, 0x00,0x0e, 0x9e,0x00, 0x00,0x00, 0xee,0xee, 0xee,0xee, 0xee,0xe0, 0x00,0xee, 0x9e,0xee, 0x07,0xe9, 0x89,0xe0, 0x00,0x0e, 0x9e,0x00, 0x00,0x00, 0x5e,0x0e, 0x00,0xee, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0x9e,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee,0xee, 0xee,0xee, 0x9e,0xe0, 0x00,0xe9, 0x89,0xee, 0x07,0xee, 0x9e,0xe0, 0x00,0x00, 0x5e,0x00, 0x00,0x0e, 0x9e,0x0e, 0x00,0xee, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0xee,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee,0xee, 0xee,0xee, 0xee,0xe0, 0x00,0xee, 0x9e,0xee, 0x07,0xe9, 0x89,0xe0, 0x00,0x0e, 0x9e,0x00, 0x00,0x00, 0x5e,0x0e, 0x00,0xee, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0x9e,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee};
Image necromancerIdleRight = Image(necromancerIdleRightData);
const uint8_t necromancerIdleLeftData[] = {8, 10, 4, 0, 4, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0x00, 0x0e,0xe9, 0xee,0x70, 0xee,0x98, 0x90,0x00, 0x0e,0xe9, 0xe0,0x00, 0x00,0xe5, 0x0e,0x00, 0xe0,0xe9, 0xee,0x00, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe9, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00,0xee, 0xee,0xee, 0xee,0xe9, 0xee,0x00, 0x0e,0x98, 0x9e,0x70, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe5, 0x00,0x00, 0x00,0xe9, 0xee,0x00, 0xe0,0xe9, 0xee,0x00, 0xee,0xe9, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00,0xe9, 0xee,0xee, 0xee,0x98, 0x9e,0x00, 0x0e,0xe9, 0xee,0x70, 0xee,0xe5, 0x00,0x00, 0x0e,0xe9, 0xe0,0x00, 0x00,0xe9, 0xee,0x00, 0xe0,0xe9, 0xee,0x00, 0xee,0xee, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00,0xee, 0xee,0xee, 0xee,0xe9, 0xee,0x00, 0x0e,0x98, 0x9e,0x70, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe5, 0x00,0x00, 0x00,0xe9, 0xee,0x00, 0xe0,0xe9, 0xee,0x00, 0xee,0xe9, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00};
Image necromancerIdleLeft = Image(necromancerIdleLeftData);
const uint8_t fireballData[] = {8, 4, 2, 0, 2, 0xFF, 1, 0x99, 0x99,0x99, 0x99,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x99, 0x99,0x99, 0x99,0xaa, 0xaa,0xaa, 0xaa,0x99, 0x99,0x99, 0x99,0x99, 0x99,0x99, 0x99,0xaa, 0xaa,0xaa, 0xaa};
Image fireball = Image(fireballData);
const uint8_t necromancerChargeRightData[] = {8, 10, 3, 0, 2, 0x0E, 1, 0xee, 0xee,0xee, 0x9e,0xe0, 0x00,0xe9, 0x89,0xee, 0x07,0xee, 0x9e,0xe0, 0x00,0x0e, 0x9e,0xee, 0x00,0xe0, 0x5e,0xee, 0x00,0x0e, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0xee,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee,0xee, 0xee,0xee, 0x8e,0xe0, 0x00,0xe8, 0x88,0xee, 0x07,0xee, 0x8e,0xe0, 0x00,0x0e, 0x9e,0xee, 0x00,0xe0, 0x5e,0xee, 0x00,0x0e, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0xee,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee,0xee, 0xee,0xe8, 0x98,0xe0, 0x00,0xe9, 0x89,0xee, 0x07,0xe8, 0x98,0xe0, 0x00,0x0e, 0x9e,0xee, 0x00,0xe0, 0x5e,0xee, 0x00,0x0e, 0x9e,0xee, 0x00,0xee, 0x9e,0xe0, 0x00,0x0e, 0xee,0xe0, 0x00,0x0e, 0xee,0x00, 0x00,0x00, 0xee};
Image necromancerChargeRight = Image(necromancerChargeRightData);
const uint8_t necromancerChargeLeftData[] = {8, 10, 3, 0, 2, 0x0E, 1, 0xe9, 0xee,0xee, 0xee,0x98, 0x9e,0x00, 0x0e,0xe9, 0xee,0x70, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe5, 0x0e,0x00, 0xee,0xe9, 0xe0,0x00, 0xee,0xe9, 0xee,0x00, 0xee,0xee, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00,0xe8, 0xee,0xee, 0xee,0x88, 0x8e,0x00, 0x0e,0xe8, 0xee,0x70, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe5, 0x0e,0x00, 0xee,0xe9, 0xe0,0x00, 0xee,0xe9, 0xee,0x00, 0xee,0xee, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00,0x89, 0x8e,0xee, 0xee,0x98, 0x9e,0x00, 0x0e,0x89, 0x8e,0x70, 0xee,0xe9, 0xe0,0x00, 0x0e,0xe5, 0x0e,0x00, 0xee,0xe9, 0xe0,0x00, 0xee,0xe9, 0xee,0x00, 0xee,0xee, 0xe0,0x00, 0x0e,0xee, 0xe0,0x00, 0x0e,0xee, 0x00,0x00, 0x00};
Image necromancerChargeLeft = Image(necromancerChargeLeftData);

Character::Character() {}

Character::Character(byte _posX, byte _posY, byte _moveDelay, byte _baseHp) {
  this->posX = _posX;
  this->posY = _posY;
  this->moveDelay = _moveDelay;
  this->moveCounter = _moveDelay;
  this->isAlive = true;
  this->baseHp = _baseHp;
  this->currentHp = _baseHp;
  this->moveDir = _right;
  this->hasLoot = false;
  this->gold = 1;
}

void Character::setPosition(byte x, byte y) {
  this->posX = x;
  this->posY = y;
}

void Character::draw(int x, int y) {
    /*if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+offsetX, y-offsetY, enemySpriteRight);
    } else {
      enemyCorpse.setFrame(0);
      gb.display.drawImage(x+corpseOffsetX, y-corpseOffsetY, rightCorpseSprite);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+offsetX, y-offsetY, enemySpriteLeft);
    } else {
      enemyCorpse.setFrame(1);
      gb.display.drawImage(x+corpseOffsetX, y-corpseOffsetY, enemySpriteLeft);
    }
  }*/
}

void Character::takeDamage(byte dmg) {
  if (currentHp - dmg) {
    currentHp -= dmg;
  } else {
    currentHp = 0;
    isAlive = false;
    hasLoot = true;
    world.enemyCount--;
    world.world[posX][posY] = world.world[posX][posY] - 3;
  }
}

void Character::changeDirection(byte dir) {
  if (dir == 0) return;
  
  this->moveDir = dir;
}

byte Character::getTurnCounter() {
  return moveDelay;
}

void Character::pickLoot() {
  hasLoot = false;
  player.gold += this->gold;
}

void Character::drawLoot(byte x, byte y) {
  if (hasLoot) {
    gb.display.drawImage(x+2, y-3, coin);
  }
}

void Character::takeAction(byte x, byte y) { }

bool Character::doesCollideWithWall(byte x, byte y) {
  byte newX = posX + x;
  byte newY = posY + y;
  
  return world.world[newX][newY] != 2;
}

Vec Character::getDirection() {
  byte counter = 0;
  Vec possibleDirs[4];
  
  for (byte i = 0; i < sizeof(directions)/sizeof(directions[0]); ++i) {
    Vec dir = directions[i];
    
    if (!this->doesCollideWithWall(dir.x, dir.y)) {
      possibleDirs[counter] = dir;
      counter++;
    }
  }

  if (counter == 0) {
    return Vec(99, 99);
  }
  
  byte rnd = random(counter);

  return possibleDirs[rnd];
}

Player::Player() { }

Player::Player(byte _posX, byte _posY)
  : Character(_posX, _posY, 0, 3) {}

void Player::init() {
  this->moveDelay = 1;
  this->moveCounter = 0;
  this->isAlive = true;
  this->baseHp = 4;
  this->currentHp = 4;
  this->gold = 0;
}

void Player::takeAction(byte x, byte y) {
  posX += x;
  posY += y;
}

void Player::takeDamage(byte dmg) {
  if (currentHp - dmg) {
    currentHp -= dmg;
    hitAnimationTime = 6;
  } else {
    currentHp = 0;
    isAlive = false;
  }
}

void Player::draw(int x, int y) {
  if (this->moveDir == _right) {
    gb.display.drawImage(x, y-4, playerSpriteRight);
  } else {
    gb.display.drawImage(x, y-4, playerSpriteLeft);
  }

  if (attackAnimationTime > 0) {
    attackAnimationTime--;
    gb.display.drawImage(attackPos.x, attackPos.y-2, slash);
  }
  if (hitAnimationTime > 0) {
    hitAnimationTime--;
    gb.display.drawImage(camera.screenPosX(posX), camera.screenPosY(posY)-2, bloodSlash);
  }
}

void Player::drawGui() {
  gb.display.setColor(RED);
  
  for (byte i = 0; i < currentHp-1; i+=2) {
    gb.display.drawImage((i/2)+6*(i/2), 0, heartGui); 
  }

  for (byte i = currentHp; i < baseHp; i+=2) {
    gb.display.drawImage((i/2)+6*(i/2), 0, heartEmptyGui); 
  }
  
  if (currentHp%2 != 0) {
    gb.display.drawImage(6*(currentHp/2)+(currentHp/2), 0, heartEmptyGui); 
    gb.display.drawImage(6*(currentHp/2)+(currentHp/2), 0, heartGui, 0, 0, 4, 8); 
  }
  
  gb.display.drawImage(0, 56, coinGui);
  gb.display.setColor(WHITE);
  gb.display.setCursor(8, 57);
  gb.display.print(gold); 
}

bool Player::doesCollideWithWall(byte x, byte y) {
  byte newX = posX + x;
  byte newY = posY + y;
  
  return world.world[newX][newY] == 1 || world.world[newX][newY] == 4;
}

Chest::Chest(byte _posX, byte _posY) : Character(_posX, _posY, 9999, 1) {
  content = 0;
  hasLoot = false;
  
  if (player.currentHp < player.baseHp) {
    byte rnd = random(0, 3);
    if(rnd == 0) {
      content = 1;
    }
  }
  gold = 10;
}

void Chest::draw(int x, int y) {
  if (isAlive) {
    chest.setFrame(0);
  } else {
    chest.setFrame(1);
  }
  gb.display.drawImage(x+2, y-2, chest);

  if (hasLoot) {
    if (content == 1) {
      gb.display.drawImage(x+2, y-3, heart);
    } else {
      gb.display.drawImage(x+2, y-3, coin);
    }
  }
}

void Chest::takeDamage(byte dmg) {
  currentHp = 0;
  isAlive = false;
  hasLoot = true;
  world.world[posX][posY] = world.world[posX][posY] - 3;
}

void Chest::pickLoot() {
  hasLoot = false;
  if (content == 1 && player.currentHp < player.baseHp) {
    player.currentHp++;
  } else {
    player.gold += this->gold;    
  }
}

Enemy::Enemy(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 2, _baseHp) { }

void Enemy::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, enemySprRight);
    } else {
      enemyCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, enemySprLeft);
    } else {
      enemyCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  }
  drawLoot(x, y);
}
  
void Enemy::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = astar.getNextTile(Vec(posX, posY), Vec(player.posX, player.posY), false);

  if (dir.x == 99 && dir.y == 99) {
    return;
  }
  
  if (dir.x-posX != 0) {
    this->changeDirection(dir.x-posX);
  }
  
  if (dir.x == player.posX && dir.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = dir.x;
    posY = dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

Skull::Skull(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 2, _baseHp) { }

void Skull::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, skullRight);
    } else {
      skullCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, skullCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, skullLeft);
    } else {
      skullCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, skullCorpse);
    }
  }
  drawLoot(x, y);
}
  
void Skull::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = getDirection();

  if (dir.x == 99 && dir.y == 99) {
    return;
  }

  if (dir.x != 0) {
    this->changeDirection(dir.x);
  }
  
  if (dir.x+posX == player.posX && dir.y+posY == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX += dir.x;
    posY += dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

BloodSkull::BloodSkull(byte _posX, byte _posY, byte _baseHp)
  : Skull(_posX, _posY, _baseHp) {
  this->moveDelay = 1;    
}

void BloodSkull::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, bloodskullRight);
    } else {
      bloodskullCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, bloodskullCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, bloodskullLeft);
    } else {
      bloodskullCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, bloodskullCorpse);
    }
  }
  drawLoot(x, y);
}

Ghost::Ghost(byte _posX, byte _posY, byte _baseHp)
  : Enemy(_posX, _posY, _baseHp) { }

void Ghost::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, ghostRight);
    } else {
      ghostCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, ghostCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, ghostLeft);
    } else {
      ghostCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, ghostCorpse);
    }
  }
  drawLoot(x, y);
}
  
void Ghost::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = astar.getNextTile(Vec(posX, posY), Vec(player.posX, player.posY), true);

  if (dir.x == 99 && dir.y == 99) {
    return;
  }

  if (dir.x-posX != 0) {
    this->changeDirection(dir.x-posX);
  }
  
  if (dir.x == player.posX && dir.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = dir.x;
    posY = dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

Rat::Rat(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 2, _baseHp) {
    currentDir = getDirection();
  }

void Rat::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+2, y-2, ratRight);
    } else {
      ratCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, ratCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, ratLeft);
    } else {
      ratCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, ratCorpse);
    }
  }
  drawLoot(x, y);
}
  
void Rat::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  if ((currentDir.x == 99 && currentDir.y == 99) || doesCollideWithWall(currentDir.x, currentDir.y)) {
    currentDir = getDirection();
    this->changeDirection(currentDir.x);
    return;
  }

  Vec nextPos = Vec(posX + currentDir.x, posY + currentDir.y);
  
  if (nextPos.x == player.posX && nextPos.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = nextPos.x;
    posY = nextPos.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

Necromancer::Necromancer(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 1, _baseHp) { 
  charge = false;
  chargeAnim = 0;
  gold = 10;    
}

void Necromancer::drawLaser() {
  if (chargeAnim > 0) {
    chargeAnim--;
    for (short i = posX + moveDir; ;i+=moveDir) {
      gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(posY), fireball);
      if (i < 0 || i >= world_size) break;
      if (world.world[i][posY] == 1 || world.world[i][posY] == 4) break;
    }
  }
}

void Necromancer::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      if (!charge) gb.display.drawImage(x+2, y-3, necromancerIdleRight);
      else gb.display.drawImage(x+2, y-3, necromancerChargeRight);
    } else {
      enemyCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  } else {    
    if(this->isAlive) {
      if (!charge) gb.display.drawImage(x+2, y-3, necromancerIdleLeft);
      else gb.display.drawImage(x+2, y-3, necromancerChargeLeft);
    } else {
      enemyCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  }
  drawLaser();
  drawLoot(x, y);
}
  
void Necromancer::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }

  if (charge) {
    for (short i = posX + moveDir; ;i+=moveDir) {
      if (i < 0 || i >= world_size) break;
      if (world.world[i][posY] == 1 || world.world[i][posY] == 4) break;
      if (i == player.posX && posY == player.posY) {
         player.takeDamage(2);
         break;
      }
    }
    charge = false;
    chargeAnim = 4;
    return;
  }
  
  Vec dir = astar.getNextTile(Vec(posX, posY), Vec(player.posX, player.posY), false);

  if (dir.x == 99 && dir.y == 99) {
    return;
  }
  if (dir.x-posX != 0) {
    this->changeDirection(dir.x-posX);
  }
  if (posY == player.posY && camera.isInBounds(posX, posY)) {
    charge = true;
    return;
  }
  
  if (dir.x == player.posX && dir.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = dir.x;
    posY = dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}


Player player;
