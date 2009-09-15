#ifndef __CITEM_H__
#define __CITEM_H__

#include "TDG.h"

#define MAX_ITEMS				53
#define ITEM_CAPACITY			5

enum ItemType
{
	ITEM_NOTHING_HERE,
	ITEM_A_HOT_WATER_BOTTLE,
	ITEM_BLANK_BULLETS,
	ITEM_A_CANDLESTICK,
	ITEM_THE_WILL,					// Clue #1
	ITEM_A_KNIFE,					// Clue #8
	ITEM_NEWSPAPER_CUTTING,
	ITEM_A_NOTE,					// Clue #4
	ITEM_A_SMALL_BOTTLE,			// Clue #6
	ITEM_A_CRAVATE,					// Clue #3
	ITEM_A_SOGGY_ENVELOPE,
	ITEM_A_LETTER,
	ITEM_SCALPELS,
	ITEM_A_SYRINGE,					// Clue #9
	ITEM_A_BOTTLE_OF_PILLS,
	ITEM_A_HAMMER,
	ITEM_A_BUNCH_OF_KEYS,
	ITEM_A_BIG_IRON_KEY,
	ITEM_A_SILVER_TRAY,
	ITEM_A_BOTTLE_OF_WINE,
	ITEM_A_COMB,
	ITEM_A_HARDBACK_BOOK,
	ITEM_A_FOLDED_DOCUMENT,			// Clue #2
	ITEM_AN_ELEPHANT_GUN,
	ITEM_A_DIARY,
	ITEM_A_BLACK_BAG,
	ITEM_COLOGNE,
	ITEM_A_SMALL_BOOK,
	ITEM_DIRTY_PLATES,
	ITEM_A_PICTURE,
	ITEM_A_WAD_OF_NOTES,			// Clue #5
	ITEM_A_LOCKET,
	ITEM_A_SCREWDRIVER,
	ITEM_AN_OPEN_LOCKET,			// Clue #10
	ITEM_BROKEN_PLATES,
	ITEM_BROKEN_GLASS,
	ITEM_SHREDDED_PAPER,
	ITEM_BOOKS1,
	ITEM_BOOKS2,
	ITEM_A_LETTER_OPENER,
	ITEM_A_JACKET,
	ITEM_NOTEBOOKS,
	ITEM_PLANS,
	ITEM_A_MIRROR,
	ITEM_CUTLERY,
	ITEM_A_PIECE_OF_CARD,
	ITEM_A_BRIEFCASE,
	ITEM_A_FOLDER,
	ITEM_A_PAPERWEIGHT,
	ITEM_PADDED_ENVELOPES,
	ITEM_A_BOMB,					// Clue #7
	ITEM_A_SMALL_KEY,
	ITEM_BULLETS
};

class CItem
{
public:
	CItem(ItemType itemType, bool evidence);
	~CItem();
	
private:
	ItemType m_itemType;
	bool m_evidence;
	
	CItem* m_itemArray[ITEM_CAPACITY];
};

#endif