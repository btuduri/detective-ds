#include <nds.h>
#include "CVideo.h"
#include "TDG.h"
#include "windows.h"
#include "Text.h"
#include "lz77.h"

CVideo::CVideo()
{
}

CVideo::~CVideo()
{
}

void CVideo::Initialize()
{
	videoSetMode(MODE_0_2D | DISPLAY_WIN0_ON | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	
	vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE_0x06400000, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	//vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	//vramSetMainBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_BG, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	
	//vramSetBankA(VRAM_A_MAIN_SPRITE);
	//vramSetBankD(VRAM_D_SUB_SPRITE);
	
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, BG0_MAP_BASE, BG0_TILE_BASE);
	bgInit(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE, BG1_TILE_BASE);
	bgInit(2, BgType_Text8bpp, BgSize_T_256x256, BG2_MAP_BASE, BG2_TILE_BASE);
	bgInit(3, BgType_Text8bpp, BgSize_T_256x256, BG3_MAP_BASE, BG3_TILE_BASE);
	
	bgInitSub(0, BgType_Text4bpp, BgSize_T_256x256, BG0_MAP_BASE_SUB, BG0_TILE_BASE_SUB);
	bgInitSub(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE_SUB, BG1_TILE_BASE_SUB);
	int bg2Sub = bgInitSub(2, BgType_Text8bpp, BgSize_T_512x256, BG2_MAP_BASE_SUB, BG2_TILE_BASE_SUB);
	int bg3Sub = bgInitSub(3, BgType_Text8bpp, BgSize_T_512x256, BG3_MAP_BASE_SUB, BG3_TILE_BASE_SUB);
	
	bgSetControlBits(bg2Sub, BG_PRIORITY_0);
	bgSetControlBits(bg3Sub, BG_PRIORITY_2);
	
	videoBgDisableSub(0);
	
	lcdMainOnBottom();
	
	dmaCopy(sprite_miscPal, SPRITE_PALETTE, sprite_miscPalLen);
	dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
	
	dmaCopy(fontTiles, BG_TILE_RAM(BG0_TILE_BASE), fontTilesLen);
	dmaCopy(fontTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) , fontTilesLen);
	
	dmaCopy(fontPal, BG_PALETTE, fontPalLen);
	dmaCopy(fontPal, BG_PALETTE_SUB, fontPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
	dmaCopy(font_largeTiles, BG_TILE_RAM(BG0_TILE_BASE) + fontTilesLen, font_largeTilesLen);
	dmaCopy(font_largeTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) + fontTilesLen, font_largeTilesLen);
	
	dmaCopy(menu_topTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), menu_topTilesLen);
	dmaCopy(menu_topMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), menu_topMapLen);
	dmaCopy(menu_topPal, BG_PALETTE_SUB, menu_topPalLen);
	
	//dmaCopy(menu_questionsTiles, BG_TILE_RAM(BG2_TILE_BASE), menu_questionsTilesLen);
	//dmaCopy(menu_questionsMap, BG_MAP_RAM(BG2_MAP_BASE), menu_questionsMapLen);
	
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	dmaCopy(menu_bottomPal, BG_PALETTE, menu_bottomPalLen);
	
	WIN_IN = WIN0_BG0 | WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN_OUT = WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN0_Y0 = 0;
	WIN0_Y1 = 192;
	WIN0_X0 = 8;
	WIN0_X1 = 248;
	
	//WIN_IN = WIN0_BG0 | WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	//WIN_OUT = WIN0_BG0 | WIN0_BG1 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	//WIN0_Y0 = 0;
	//WIN0_Y1 = 80;
	//WIN0_X0 = 0;
	//WIN0_X1 = 255;
	
	//WIN_IN |= WIN1_BG0 | WIN1_BG1 | WIN1_BG2 | WIN1_BG3 | WIN1_SPRITES | WIN1_BLENDS;
	//WIN_OUT |= WIN1_BG1 | WIN1_BG2 | WIN1_BG3 | WIN1_SPRITES | WIN1_BLENDS;
	//WIN1_Y0 = 0;
	//WIN1_Y1 = 192;
	//WIN1_X0 = 8;
	//WIN1_X1 = 248;
	
	//oamInit(&oamMain, SpriteMapping_1D_32, false);
	//oamInit(&oamSub, SpriteMapping_1D_32, false);
	
	oamInit(&oamMain, SpriteMapping_Bmp_1D_128, false);
	oamInit(&oamSub, SpriteMapping_Bmp_1D_128, false);
}