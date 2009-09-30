#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

const char* g_characterText[] =
{
	"INSPECTOR SNIDE:\nSCOTLAND YARD DETECTIVE PLAYED BY YOURSELF.",
	"REVERAND WRINKLEBUM:\nLOCAL VICAR WHOSE WIFE DISSAPEARED IN MYSTERIOUS CIRCUMSTANCES",
	"BENTLEY THE BUTLER:\nLIFELONG SERVANT TO THE MCFUNGUS FAMILY. EXHIBITS SLIGHTLY HOSTILE BEHAVIOR..",
	"HILDA CRUMBLE:\nFAMILY COOK. NOTORIOUS FOR HER MACARONI CHEESE.",
	"GABRIEL GASBAG:\nTHE MAID. OBEDIENT AND AGREEABLE, BUT NOT VERY BRIGHT.",
	"CYNTHIA SLUDGEBUCKET:\nARROGANT AND SELF CENTRED DAUGHTER OF THE MAJOR.",
	"PROFESSOR BULL:\nOLD FRIEND OF THE LATE MR. MCFUNGUS. SCATTERBRAINED AND COMPLETELY MAD.",
	"DOCTOR MORTEM:\nSHORTSIGHTED FAMILY DOCTOR.",
	"MAJOR SLUDGEBUCKET:\nRETIRED MAJOR. DISTURBED BUT HARMLESS.",
	"MR DINGLE:\nFAMILY SOLICITOR. HERE TO READ THE WILL."
};

const char* g_characterName[] =
{
	"SNIDE",
	"THE REVEREND",
	"BENTLEY",
	"COOK",
	"GABRIEL",
	"CYNTHIA",
	"THE PROFESSOR",
	"THE DOCTOR",
	"THE MAJOR",
	"DINGLE",
	"ANGUS"
};

const char* g_itemName[] =
{
	"NOTHING HERE",
	"A HOT WATER BOTTLE",
	"BLANK BULLETS",
	"A CANDLESTICK",
	"THE WILL#",						// Clue #1
	"A KNIFE#",							// Clue #8
	"NEWSPAPER CUTTING",
	"A NOTE#",							// Clue #4
	"A SMALL BOTTLE",					// Clue #6 (Not marked)
	"A CRAVATE#",						// Clue #3
	"A SOGGY ENVELOPE",
	"A LETTER",
	"SCALPELS",
	"A SYRINGE#",						// Clue #9
	"A BOTTLE OF PILLS",
	"A HAMMER",
	"A BUNCH OF KEYS",
	"A BIG IRON KEY",
	"A SILVER TRAY",
	"A BOTTLE OF WINE",
	"A COMB",
	"A HARDBACK BOOK",
	"A FOLDED DOCUMENT#",				// Clue #2
	"AN ELEPHANT GUN",
	"A DIARY",
	"A BLACK BAG",
	"COLOGNE",
	"A SMALL BOOK",
	"DIRTY PLATES",
	"A PICTURE",
	"A WAD OF NOTES",					// Clue #5 (Not marked)
	"A LOCKET",
	"A SCREWDRIVER",
	"AN OPEN LOCKET",					// Clue #10 (Not marked)
	"BROKEN PLATES",
	"BROKEN GLASS",
	"SHREDDED PAPER",
	"BOOKS",
	"BOOKS",
	"A LETTER OPENER",
	"A JACKET",
	"NOTEBOOKS",
	"PLANS",
	"A MIRROR",
	"CUTLERY",
	"A PIECE OF CARD",
	"A BRIEFCASE",
	"A FOLDER",
	"A PAPERWEIGHT",
	"PADDED ENVELOPES",
	"A BOMB!",							// Clue #7 (Not marked)
	"A SMALL KEY",
	"BULLETS",
	"SWORD",
	"BALL ON CHAIN",
	"HOURGLASS",
	"GOLDEN SKULL",
	"RED KEY",
	"FIREPLACE BELLOW",
	"WASHING POWDER",
	"DIRTY SHIRT"
};

const char* g_itemExamine[] =
{
	"YOU FIND NOTHING OF INTEREST.",
	"HIGHEST QUALITY, WITH A FURRY COVER", // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	"IT'S BIG AND HEFTY..", // A CANDLESTICK
	NULL, // THE WILL;
	"THE BLADE DRIPS BLOOD!", // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	"IT'S MARKED WITH A SKULL AND CROSSBONES!", // A SMALL BOTTLE
	"LOOKS LIKE ONE OF THE MAJORS", // A CRAVATE;
	"IT'S ADDRESSED TO 'CUDDLES'..", // A SOGGY ENVELOPE
	NULL, // A LETTER
	"SURGICAL SCALPELS", // SCALPELS
	"THE NEEDLE DRIPS A THICK, SWEET SMELLING LIQUID", // A SYRINGE;
	"THE LABEL READS:\n\nWARNING! MEDICATED USE ONLY", // A BOTTLE OF PILLS
	NULL, // A HAMMER
	"ALL DIFFERENT SIZES", // A BUNCH OF KEYS
	"IT'S RUSTY", // A BIG IRON KEY
	"IT'S INSCRIBED:\n\nTO ANGUS MCFUNGUS, BORN 21 MARCH 1919", // A SILVER TRAY
	"NO WINE LEFT..", // A BOTTLE OF WINE
	"YUK! ..IT'S ALL GREASY", // A COMB
	"THE FADED TITLE READS:\n\n101 DETECTIVE STORIES", // A HARDBACK BOOK
	"IT'S A COPY OF MR. MCFUNGUS' WILL!", // A FOLDED DOCUMENT;
	"IT'S LOADED!", // AN ELEPHANT GUN
	"IT'S ANGUS' DIARY", // A DIARY
	"IT'S THE DOCTORS BAG", // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
	"THEY'RE ENCRUSTED WITH COOKS MACARONI CHEESE", // DIRTY PLATES
	NULL, // A PICTURE
	"A TOTAL OF $2000", // A WAD OF NOTES
	"IT'S LOCKED", // A LOCKET
	NULL, // A SCREWDRIVER
	"IT CONTAINS A WEDDING PHOTO OF GABRIEL AND DINGLE!", // AN OPEN LOCKET
	NULL, // BROKEN PLATES
	NULL, // BROKEN GLASS
	NULL, // SHREDDED PAPER
	NULL, // BOOKS
	NULL, // BOOKS
	NULL, // A LETTER OPENER
	NULL, // A JACKET
	"THEY'RE HARDBACK RING BINDERS BULGING WITH TATTY BITS OF PAPER", // NOTEBOOKS
	"THEY'RE PLANS OF THE CASTLE AND SHOW SECRET PASSAGES IN THE KITCHEN AND IN THE BEDROOMS", // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
	"IT'S DINGLES", // A BRIEFCASE
	"IT CONTAINS A VAST STAMP COLLECTION", // A FOLDER
	"IT'S MADE OF CHINA", // A PAPERWEIGHT
	"THERE ARE 10 ENVELOPES ALL MARKED 'EVIDENCE' YOU MUST FILL ALL OF THEM BEFORE YOU SOLVE THE MURDER", // PADDED ENVELOPES
	"JUST YOUR AVERAGE BOMB..", // A BOMB!
	NULL, // A SMALL KEY
	"SHOULD FIT A REVOLVER", // BULLETS
	NULL, // SWORD
	NULL, // BALL ON CHAIN
	NULL, // HOURGLASS
	NULL, // GOLDEN SKULL
	NULL, // RED KEY
	NULL, // FIREPLACE BELLOW
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
};

const char* g_itemRead[] =
{
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	"BRIEFLY, THE WILL LEAVES DONATIONS TO VARIOUS CHARITIES AND RELATIVES, $10000 TO COOK, THE PROFESSOR, THE MAJOR AND THE CHURCH. THE REST, WHICH COMES TO $1000000 IS LEFT TO GABRIEL GASBAG.", // THE WILL;
	NULL, // A KNIFE;
	"ITS THE MARRIAGES COLUMN OF 'THE TIMES'", // NEWSPAPER CUTTING
	"A TYPED MESSAGE READS:\n\n10000 IS A SMALL FRACTION OF A MILLION... YOU'LL NEVER HEAR FROM ME AGAIN.", // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	"IT'S A LOVE NOTE..I CAN'T READ THIS.. IT'S FAR TOO SLOPPY!", // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	"IT'S FULL OF SHORT DETECTIVE STORIES.. NOT VERY INTERESTING.", // A HARDBACK BOOK
	"IT'S A COPY OF THE WILL. IT LEAVES A LARGE AMOUNT TO THE PROFESSOR AND VARIOUS CHARITIES AND $10000 EACH TO THE HOUSE STAFF AND THE MAJOR.", // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	"YOU FIND NOTHING SIGNIFICANT..", // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	"IT'S ALL ABOUT MAKING A WILL.", // A SMALL BOOK
	NULL, // DIRTY PLATES
	NULL, // A PICTURE
	NULL, // A WAD OF NOTES
	NULL, // A LOCKET
	NULL, // A SCREWDRIVER
	NULL, // AN OPEN LOCKET
	NULL, // BROKEN PLATES
	NULL, // BROKEN GLASS
	NULL, // SHREDDED PAPER
	NULL, // BOOKS
	NULL, // BOOKS
	NULL, // A LETTER OPENER
	NULL, // A JACKET
	"I CAN'T UNDERSTAND A WORD OF IT..", // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	"IT READS:\n\nSAM WAS HERE", // A PIECE OF CARD
	NULL, // A BRIEFCASE
	NULL, // A FOLDER
	NULL, // A PAPERWEIGHT
	NULL, // PADDED ENVELOPES
	NULL, // A BOMB!
	NULL, // A SMALL KEY
	NULL, // BULLETS
	NULL, // SWORD
	NULL, // BALL ON CHAIN
	NULL, // HOURGLASS
	NULL, // GOLDEN SKULL
	NULL, // RED KEY
	NULL, // FIREPLACE BELLOW
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
};

const char* g_colName[] =
{
	"NOTHING HERE",
	"NOTHING HERE",				// DOOR1
	"NOTHING HERE",				// DOOR2
	"NOTHING HERE",				// DOOR3
	"NOTHING HERE",				// DOOR4
	"NOTHING HERE",				// DOOR5
	"NOTHING HERE",				// DOOR6
	"NOTHING HERE",				// DOOR7
	"NOTHING HERE",				// DOOR8
	"NOTHING HERE",				// WALL
	"A DUMMY",
	"A FOUR POSTER BED",
	"A CHEST OF DRAWERS",
	"A FIREPLACE",
	"A COAL BUCKET",
	"A PAINTING",
	"A WOODEN BOX",
	"A MICROWAVE",
	"A SIDEBOARD",
	"A CUPBOARD",
	"A CUPBOARD",
	"A CUPBOARD",
	"A CUPBOARD",
	"A SINK",
	"A STAIRCASE",
	"A BOOKCASE",
	"A BOOKCASE",
	"BOXES",
	"BOXES",
	"BOXES",
	"A BED",
	"A CLOTHES CUPBOARD",
	"A CLOCK",
	"A WINDOW",
	"A DESK",
	"SHELVES",
	"A LOCKED WALL SAFE",
	"AN OPEN WALL SAFE",
	"DINGLE'S BODY!",
	"A PIANO AND A SQUASHED CYNTHIA SLUDGEBUCKET!",
	"GABRIEL'S BODY!",
	"THE STABBED DOCTOR!",
	"THE LATE MR MCFUNGUS' HEADSTONE",
	"A HEADSTONE",
	"A FOUNTAIN",
	"A FOUNTAIN",
	"A GARGOYLE",
	"A GARGOYLE",
	"A GARGOYLE",
	"A GOAT LIKE PAINTING",
	"A DESK WITH A STATUE",
	"A TROPHY",
	"A BOOKCASE",
	"A KNIGHT",
	"A COUCH",
	"AN HOURGLASS",
	"A GOLDEN SKULL",
	"A TABLE",
	"A BROOM",
	"A WASHING MACHINE",
	"A WASHING BASKET",
	"A CUPBOARD",
	"A WOODEN CABINET",
	"A GLASS CABINET"
};

const char* g_askAboutCharacter[] =
{
	// Snide
	NULL, 										// Snide
	NULL, 										// The Reverend
	NULL, 										// Bently
	NULL,										// Cook
	NULL, 										// Gabriel
	NULL,  										// Cynthia
	NULL,										// The Professor
	NULL, 										// The Doctor
	NULL, 										// The Major
	NULL, 										// Dingle
	NULL,										// Angus

	// The Reverend	
	NULL,										// Snide
	NULL,										// The Reverend
	"\"IT'S NONE OF MY BUSINESS\"",				// Bently
	"\"ER..YES.. A FINE COOK..\"",				// Cook
	"\"IT'S NONE OF MY BUSINESS\"",				// Gabriel
	"\"MMM..FAR TOO SELF ASSURED.\"",			// Cynthia
	"\"IT'S NONE OF MY BUSINESS\"",				// The Professor
	"\"IT'S NONE OF MY BUSINESS\"",				// The Doctor
	"\"I THINK SOMEONE SHOULD PUT HIM OUT OF HIS MISERY!\"",	// The Major
	"\"DON'T BELIEVE A WORD HE SAYS\"",			// Dingle
	"\"..YES, A MOST VALUABLE PARISHIONER..MAY HE REST IN PEACE.\"",	// Angus
	
	// Bentley
	NULL,										// Snide
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// The Reverend
	NULL,										// Bently
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// Cook
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// Gabriel
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// Cynthia
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// The Professor
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// The Doctor
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// The Major
	"\"I'M VERY BUSY AT THE MOMENT SIR\"",		// Dingle
	"\"I FEEL IT WOULD BE IMPROPER, SIR, TO DISCUSS MY LATE EMPLOYER WITH A STRANGER..\"",	// Angus
	
	// Cook
	NULL,										// Snide
	"\"DON'T REALLY KNOW MUCH.\"",				// The Reverend
	"\"DON'T REALLY KNOW MUCH.\"",				// Bently
	NULL, 										// Cook
	"\"DON'T REALLY KNOW MUCH.\"",				// Gabriel
	"\"DON'T REALLY KNOW MUCH.\"",				// Cynthia
	"\"DON'T REALLY KNOW MUCH.\"",				// The Professor
	"\"DON'T REALLY KNOW MUCH.\"",				// The Doctor
	"\"DON'T REALLY KNOW MUCH.\"",				// The Major
	"\"DON'T REALLY KNOW MUCH.\"",				// Dingle
	"COOK SPEAKS \"NOT MUCH TO SAY REALLY..OF COURSE HE WILL BE MISSED.\"",	// Angus

	// Gabriel
	NULL, 										// Snide
	"\"..I'VE HEARD HE MURDERED HIS WIFE..\"",	// The Reverend
	"\"WELL, I MUSTN'T GOSSIP.\"",				// Bently
	"\"..WELL I THINK SHE'S IN LOVE..\"",		// Cook
	NULL, 										// Gabriel
	"\"SHE'S SO STUCK UP!\"",					// Cynthia
	"\"..OH HE'S A DEAR.\"",					// The Professor
	"\"I DON'T TRUST HIM!\"",					// The Doctor
	"\"..COMPLETELY MAD.\"",					// The Major
	"\"WELL, I MUSTN'T GOSSIP.\"",				// Dingle
	"GABRIEL SPEAKS \"A GOOD MAN SIR, VERY GENEROUS..MADE A BIG DONATION TO THE CHURCH ROOF FUND, SO MAVIS BAGWORTHY SAYS.\"",	// Angus

	// Cynthia
	NULL,  										// Snide
	"\"YES I TOTALLY AGREE, DARLING..\"",		// The Reverend
	"\"YES I TOTALLY AGREE, DARLING..\"",		// Bently
	"\"YES I TOTALLY AGREE, DARLING..\"",		// Cook
	"\"YES I TOTALLY AGREE, DARLING..\"",		// Gabriel
	NULL, 										// Cynthia
	"\"YES I TOTALLY AGREE, DARLING..\"",		// The Professor
	"\"YES I TOTALLY AGREE, DARLING..\"",		// The Doctor
	"\"YES I TOTALLY AGREE, DARLING..\"",		// The Major
	"\"YES I TOTALLY AGREE, DARLING..\"",		// Dingle
	"CYNTHIA SPEAKS \"SIMPLY AWFUL BUSINESS. I DIDN'T KNOW HIM, BUT PATER WAS TERRIBLY UPSET.\"",	// Angus

	// The Professor
	NULL, 										// Snide
	NULL, 										// The Reverend
	NULL, 										// Bently
	NULL,										// Cook
	NULL, 										// Gabriel
	NULL,  										// Cynthia
	NULL,										// The Professor
	NULL, 										// The Doctor
	NULL, 										// The Major
	NULL, 										// Dingle
	"THE PROFESSOR SPEAKS \"ER WHAT..OH YES..GREAT SHAME.. I HAD KNOWN HIM SINCE OXFORD.. POOR FELLOW HAD A TERRIBLE MEMORY FOR NUMBERS..\"",	// Angus

	// The Doctor
	NULL,  										// Snide
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// The Reverend
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// Bently
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// Cook
	"\"BETWEEN YOU AND ME SHE HASN'T GOT TWO BRAIN CELLS TO RUB TOGETHER\"",	// Gabriel
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// Cynthia
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// The Professor
	NULL, 										// The Doctor
	"\"HE CAN'T HAVE LONG LEFT\"", 				// The Major
	"\"CAN'T TELL YOU MUCH I'M AFRAID.\"",		// Dingle
	"\"YES, A DIABOLICAL AFFAIR THIS ..WHOEVER WAS RESPONSIBLE KNEW WHAT THEY WERE DOING..\"",	// Angus

	// The Major
	NULL,										// Snide
	NULL,										// The Reverend
	NULL, 										// Bently
	NULL, 										// Cook
	NULL, 										// Gabriel
	NULL, 										// Cynthia
	NULL, 										// The Professor
	NULL, 										// The Doctor
	NULL, 										// The Major
	NULL, 										// Dingle
	"THE MAJOR SPEAKS \"YES, DAMN SHAME.. POOR FELLOW ..\"",	// Angus

	// Dingle
	NULL, 										// Snide
	"\"SORRY, NO COMMENT\"",					// The Reverend
	"\"SORRY, NO COMMENT\"",					// Bently
	"\"SORRY, NO COMMENT\"",					// Cook
	"\"SORRY, NO COMMENT\"",					// Gabriel
	"\"SORRY, NO COMMENT\"",					// Cynthia
	"\"SORRY, NO COMMENT\"",					// The Professor
	"\"SORRY, NO COMMENT\"",					// The Doctor
	"\"SORRY, NO COMMENT\"", 					// The Major
	NULL, 										// Dingle
	"DINGLE SPEAKS \"MOST TRAGIC. OF COURSE I AM NOT AT LIBERTY TO DISCUSS HIS BUSINESS AFFAIRS.\""	// Angus
};

const char* g_iconName[] =
{
	"NONE",
	"OPEN",
	"EXAMINE",
	"INVENTORY",
	"DROP",
	"SAVE",
	"LOAD",
	"SHOOT",
	"ACCUSE",
	"DOOR_OPEN",
	"DOOR_CLOSE",
	"USE_KEY",
	"QUESTION",
	"READ",
	"CONSUME",
	"USE",
	"TIME",
	"PLACE",
	"BAG"
};

const char* g_roomName[] =
{
	"SNIDE",
	"REVEREND",
	"BENTLEY",
	"COOK",
	"GABRIEL",
	"CYNTHIA",
	"PROFESSOR",
	"DOCTOR",
	"MAJOR",
	"DINGLE",
	"OUTSIDE1",
	"OUTSIDE2",
	"OUTSIDE3",
	"OUTSIDE4",
	"PASSAGE1",
	"PASSAGE2",
	"PASSAGE3",
	"HALL1",
	"HALL2",
	"HALL3",
	"HALL4",
	"LANDING",
	"KITCHEN",
	"STAIRS",
	"STUDY",
	"CLOCK",
	"CELLAR",
	"DRAWING",
	"LIBRARY",
	"GARDEN",
	"GRAVEYARD",
	"COURTYARD",
	"ANGUS' LANDING",
	"ANGUS' ROOM",
	"ANGUS' SECRET ROOM",
	"ANGUS' STAIRS",
	"DINING"
};

const char* g_enterRoomText[] =
{
	"YOU ARE IN YOUR ROOM.",
	"YOU ARE IN THE REVEREND'S ROOM.",
	"YOU ARE IN BENTLEY'S ROOM.",
	"YOU ARE IN COOK'S ROOM.",
	"YOU ARE IN GABRIEL'S ROOM.",
	"YOU ARE IN CYNTHIA'S ROOM.",
	"YOU ARE IN THE PROFESSOR'S ROOM.",
	"YOU ARE IN THE DOCTOR'S ROOM.",
	"YOU ARE IN THE MAJOR'S ROOM.",
	"YOU ARE IN DINGLE'S ROOM.",
	"",										// Outside 1
	"",										// Outside 2
	"",										// Outside 3
	"",										// Outside 4
	"YOU ARE OUTSIDE",						// Passage 1
	"",										// Passage 2
	"",										// Passage 3
	"",										// Hall 1
	"",										// Hall 2
	"",										// Hall 3
	"",										// Hall 4
	"YOU ARE ON THE LANDING.",
	"YOU ARE IN THE KITCHEN",
	"YOU ARE IN THE HALL",
	"YOU ARE IN THE STUDY",
	"",										// Clock
	"YOU ARE IN THE CELLAR",
	"YOU ARE IN THE DRAWING ROOM",
	"YOU ARE IN THE LIBRARY",
	"YOU ARE IN THE UTILITY ROOM",
	"YOU ARE IN THE GARDEN",
	"YOU ARE IN HE GRAVEYARD",
	"YOU ARE IN THE COURTYARD",
	"YOU ARE ON MR MCFUNGUS' LANDING",
	"YOU ARE IN MR MCFUNGUS' ROOM",
	"YOU ARE IN MR MCFUNGUS' SECRET ROOM",
	"YOU ARE IN MR MCFUNGUS' STAIRCASE",
	"YOU ARE IN THE DINING ROOM"
};

const char* g_KeyboardText[] =
{
	"    1 2 3 4 5 6 7 8 9 0 EXIT    ",
	"                                ",
	"    Q W E R T Y U I O P BKSP    ",
	"                                ",
	"     A S D F G H J K L ENTER    ",
	"                                ",
	"      Z X C V B N M  SPACE      "
};

const char* g_KeyboardHit[] =
{
	"\000\000\000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\000\e\e\e\e\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000Q\000W\000E\000R\000T\000Y\000U\000I\000O\000P\000\b\b\b\b\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000\000A\000S\000D\000F\000G\000H\000J\000K\000L\000\n\n\n\n\n\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000\000\000Z\000X\000C\000V\000B\000N\000M\000\000     \000\000\000\000\000\000"
};

const int g_largeTextMap[] =
{
	0x00,0x20,0x21,0x00,0x00,0x00,0x00,0x23,0x00,0x00,0x00,0x00,0x1C,0x1F,0x1B,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0x1E,0x00,0x00,0x00,0x00,
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x00,0x00,0x00,0x00,0x00,
	0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void DrawChar(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = c - 0x20;
}

void DrawString(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(u32 i=0; i<strlen(string); i++)
		*pMap++ = string[i] - 0x20;
}

void DrawString(const char* string, int x, int y, int count, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(u32 i=0; i<strlen(string) && i < count; i++)
		*pMap++ = string[i] - 0x20;
}

void DrawStringLarge(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(u32 i=0; i<strlen(string); i++)
	{	
		*pMap = 96 * 2 + g_largeTextMap[string[i] - 0x20] * 2;
		*(pMap+32) = 96 * 2 + g_largeTextMap[string[i] - 0x20] * 2 + 1;
		pMap++;
	}
}

void DrawCharLarge(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = 96 * 2 + g_largeTextMap[c - 0x20] * 2;
	*(pMap+32) = 96 * 2 + g_largeTextMap[c - 0x20] * 2 + 1;
}

