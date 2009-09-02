#include "TDG.h"

const int g_snideHeadFrames[] = { FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK | FRAME_DOWN, FRAME_RIGHT, FRAME_UP, FRAME_LEFT, FRAME_DEAD };
const int g_snideBodyFrames[] = { FRAME_SPEAK | FRAME_DOWN, FRAME_DOWN, FRAME_DOWN, FRAME_DOWN, FRAME_RIGHT, FRAME_RIGHT, FRAME_RIGHT, FRAME_RIGHT, FRAME_UP, FRAME_UP, FRAME_UP, FRAME_UP, FRAME_LEFT, FRAME_LEFT, FRAME_LEFT, FRAME_LEFT, FRAME_DEAD };
const int g_reverendHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_reverendBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_bentleyHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_bentleyBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_cookHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_cookBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_gabrielHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_gabrielBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_cynthiaHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_cynthiaBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_professorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_professorBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_doctorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_doctorBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_majorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_majorBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_dingleHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_dingleBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_angusHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_angusBodyFrames[] = { FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };

MAP g_cellarMap = { 400, 192, map_cellarTiles, map_cellarTilesLen, map_cellarMap, map_cellarMapLen, map_cellarPal, map_cellarPalLen };
MAP g_clockMap = { 304, 192, map_clockTiles, map_clockTilesLen, map_clockMap, map_clockMapLen, map_clockPal, map_clockPalLen };
MAP g_drawingMap = { 640, 192, map_drawingTiles, map_drawingTilesLen, map_drawingMap, map_drawingMapLen, map_drawingPal, map_drawingPalLen };
MAP g_hall1Map = { 832, 192, map_hall1Tiles, map_hall1TilesLen, map_hall1Map, map_hall1MapLen, map_hall1Pal, map_hall1PalLen };
MAP g_hall2Map = { 832, 192, map_hall2Tiles, map_hall2TilesLen, map_hall2Map, map_hall2MapLen, map_hall2Pal, map_hall2PalLen };
MAP g_hall3Map = { 832, 192, map_hall3Tiles, map_hall3TilesLen, map_hall3Map, map_hall3MapLen, map_hall3Pal, map_hall3PalLen };
MAP g_hall4Map = { 544, 192, map_hall4Tiles, map_hall4TilesLen, map_hall4Map, map_hall4MapLen, map_hall4Pal, map_hall4PalLen };
MAP g_kitchenMap = { 536, 192, map_kitchenTiles, map_kitchenTilesLen, map_kitchenMap, map_kitchenMapLen, map_kitchenPal, map_kitchenPalLen };
MAP g_landingMap = { 400, 192, map_landingTiles, map_landingTilesLen, map_landingMap, map_landingMapLen, map_landingPal, map_landingPalLen };
MAP g_libraryMap = { 416, 192, map_libraryTiles, map_libraryTilesLen, map_libraryMap, map_libraryMapLen, map_libraryPal, map_libraryPalLen };
MAP g_outside1Map = { 400, 192, map_outside1Tiles, map_outside1TilesLen, map_outside1Map, map_outside1MapLen, map_outside1Pal, map_outside1PalLen };
MAP g_outside2Map = { 544, 192, map_outside2Tiles, map_outside2TilesLen, map_outside2Map, map_outside2MapLen, map_outside2Pal, map_outside2PalLen };
MAP g_passage1Map = { 256, 192, map_passage1Tiles, map_passage1TilesLen, map_passage1Map, map_passage1MapLen, map_passage1Pal, map_passage1PalLen };
MAP g_passage2Map = { 256, 192, map_passage2Tiles, map_passage2TilesLen, map_passage2Map, map_passage2MapLen, map_passage2Pal, map_passage2PalLen };
MAP g_room1Map = { 400, 192, map_room1Tiles, map_room1TilesLen, map_room1Map, map_room1MapLen, map_room1Pal, map_room1PalLen };
MAP g_room2Map = { 344, 192, map_room2Tiles, map_room2TilesLen, map_room2Map, map_room2MapLen, map_room2Pal, map_room2PalLen };
MAP g_stairsMap = { 336, 192, map_stairsTiles, map_stairsTilesLen, map_stairsMap, map_stairsMapLen, map_stairsPal, map_stairsPalLen };
MAP g_studyMap = { 320, 192, map_studyTiles, map_studyTilesLen, map_studyMap, map_studyMapLen, map_studyPal, map_studyPalLen };
MAP g_gardenMap = { 304, 192, map_gardenTiles, map_gardenTilesLen, map_gardenMap, map_gardenMapLen, map_gardenPal, map_gardenPalLen };
MAP g_graveyardMap = { 304, 192, map_graveyardTiles, map_graveyardTilesLen, map_graveyardMap, map_graveyardMapLen, map_graveyardPal, map_graveyardPalLen };

MAP g_landing_front1Map = { 400, 192, map_landing_front1Tiles, map_landing_front1TilesLen, map_landing_front1Map, map_landing_front1MapLen };
MAP g_landing_front2Map = { 400, 192, map_landing_front2Tiles, map_landing_front2TilesLen, map_landing_front2Map, map_landing_front2MapLen };
MAP g_outside2_frontMap = { 544, 192, map_outside2_frontTiles, map_outside2_frontTilesLen, map_outside2_frontMap, map_outside2_frontMapLen };
MAP g_stairs_frontMap = { 336, 192, map_stairs_frontTiles, map_stairs_frontTilesLen, map_stairs_frontMap, map_stairs_frontMapLen };
MAP g_garden_frontMap = { 304, 192, map_garden_frontTiles, map_garden_frontTilesLen, map_garden_frontMap, map_garden_frontMapLen };
MAP g_graveyard_frontMap = { 304, 192, map_graveyard_frontTiles, map_graveyard_frontTilesLen, map_graveyard_frontMap, map_graveyard_frontMapLen };

mm_sound_effect g_sfx_footsteps = { { SFX_FOOTSTEPS } , (int)(1.0f * (1<<10)), 0,	255, 127 };