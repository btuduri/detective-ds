#include <nds.h>

enum CollisionType
{
	COL_NOTHING_HERE = 0,
	COL_DOOR1 = 1,
	COL_DOOR2 = 2,
	COL_DOOR3 = 3,
	COL_DOOR4 = 4,
	COL_DOOR5 = 5,
	COL_DOOR6 = 6,
	COL_DOOR7 = 7,
	COL_SECRET_PASSAGE = 8,
	COL_FLOOR = 9,
	COL_WALL = 10,
	COL_BOOKCASE = 11,
	COL_PAINTING = 12,
	COL_SAFE = 13,
	COL_COAL_BUCKET = 14,
	COL_FIREPLACE = 15,
	COL_CLOCK = 16,
	COL_CUPBOARD = 17,
	COL_MICROWAVE = 18,
	COL_WOODEN_BOX = 19,
	COL_SINK = 20,
	COL_BOXES = 21,
	COL_CLOTHES_CUPBOARD = 22,
	COL_BED = 23,
	COL_CHEST_OF_DRAWERS = 24,
	COL_FOUR_POSTER_BED = 25,
	COL_WINDOW = 26
};

extern const u8 col_hall1[];
extern const u8 col_room1[];
