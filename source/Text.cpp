#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

const char* g_characterText[MAX_CHARACTERS] =
{
	"INSPECTOR SNIDE:\n\nSCOTLAND YARD DETECTIVE PLAYED BY YOURSELF.",
	"REVERAND WRINKLEBUM:\n\nLOCAL VICAR WHOSE WIFE DISAPPEARED IN MYSTERIOUS CIRCUMSTANCES.",
	"BENTLEY THE BUTLER:\n\nLIFELONG SERVANT TO THE MCFUNGUS FAMILY. EXHIBITS SLIGHTLY HOSTILE BEHAVIOR.",
	"HILDA CRUMBLE:\n\nFAMILY COOK. NOTORIOUS FOR HER MACARONI CHEESE.",
	"GABRIEL GASBAG:\n\nTHE MAID. OBEDIENT AND AGREEABLE, BUT NOT VERY BRIGHT.",
	"CYNTHIA SLUDGEBUCKET:\n\nARROGANT AND SELF CENTRED DAUGHTER OF THE MAJOR.",
	"PROFESSOR BULL:\n\nOLD FRIEND OF THE LATE MR. MCFUNGUS. SCATTERBRAINED AND COMPLETELY MAD.",
	"DOCTOR MORTEM:\n\nSHORTSIGHTED FAMILY DOCTOR.",
	"MAJOR SLUDGEBUCKET:\n\nRETIRED MAJOR. DISTURBED BUT HARMLESS.",
	"MR. DINGLE:\n\nFAMILY SOLICITOR. HERE TO READ THE WILL.",
	"ANGUS MCFUNGUS:\n\nTHE GENEROUS AND DEEPLY RELIGIOUS ARISTOCRAT WHO HAS BEEN MURDERED."
};

const char* g_characterName[MAX_CHARACTERS] =
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
	"MR. MCFUNGUS"
};

const char* g_itemName[MAX_ITEMS] =
{
	"NOTHING HERE",
	"A HOT WATER BOTTLE",
	"BLANK BULLETS",
	"A CANDLESTICK",
	"THE WILL#",						// Clue #1
	"A KNIFE#",							// Clue #8
	"NEWSPAPER CUTTING",
	"A NOTE#",							// Clue #4
	"A SMALL BOTTLE#",					// Clue #6 (Not marked)
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
	"A WAD OF NOTES#",					// Clue #5 (Not marked)
	"A LOCKET",
	"A SCREWDRIVER",
	"AN OPEN LOCKET#",					// Clue #10 (Not marked)
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
	"A BOMB!#",							// Clue #7
	"A SMALL KEY",
	"BULLETS",
	"A SWORD",
	"A BALL ON CHAIN",
	"AN HOURGLASS",
	"A GOLDEN SKULL",
	"A RED KEY",
	"A VACUUM CLEANER",
	"WASHING POWDER",
	"A DIRTY SHIRT",
	"ANGUS MCFUNGUS",
	"A HIDDEN KEY"
};

const char* g_itemExamine[MAX_ITEMS] =
{
	"YOU FIND NOTHING OF INTEREST.",
	"HIGHEST QUALITY, WITH A FURRY COVER.", // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	"IT'S BIG AND HEFTY..", // A CANDLESTICK
	NULL, // THE WILL;
	"THE BLADE DRIPS BLOOD!", // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	"IT'S MARKED WITH A SKULL AND CROSSBONES! THE LIQUID INSIDE SMELLS SWEET.", // A SMALL BOTTLE
	"LOOKS LIKE ONE OF THE MAJOR'S.", // A CRAVATE;
	"IT'S ADDRESSED TO 'CUDDLES'..", // A SOGGY ENVELOPE
	NULL, // A LETTER
	"SURGICAL SCALPELS.", // SCALPELS
	"THE NEEDLE DRIPS A THICK, SWEET SMELLING LIQUID.", // A SYRINGE;
	"THE LABEL READS:\n\nWARNING! MEDICATED USE ONLY.", // A BOTTLE OF PILLS
	NULL, // A HAMMER
	"ALL DIFFERENT SIZES.", // A BUNCH OF KEYS
	"IT'S RUSTY.", // A BIG IRON KEY
	"IT'S INSCRIBED:\n\nTO ANGUS MCFUNGUS, BORN 21 MARCH 1919.", // A SILVER TRAY
	"NO WINE LEFT..", // A BOTTLE OF WINE
	"YUK! ..IT'S ALL GREASY.", // A COMB
	"THE FADED TITLE READS:\n\n101 DETECTIVE STORIES.", // A HARDBACK BOOK
	"IT'S A COPY OF MR. MCFUNGUS' WILL!", // A FOLDED DOCUMENT;
	"IT'S LOADED!", // AN ELEPHANT GUN
	"IT'S ANGUS' DIARY.", // A DIARY
	"IT'S THE DOCTORS BAG.", // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
	"THEY'RE ENCRUSTED WITH COOK'S MACARONI CHEESE.", // DIRTY PLATES
	NULL, // A PICTURE
	"A TOTAL OF $2000.", // A WAD OF NOTES
	"IT'S LOCKED.", // A LOCKET
	NULL, // A SCREWDRIVER
	"IT CONTAINS A WEDDING PHOTO OF GABRIEL AND DINGLE!", // AN OPEN LOCKET
	NULL, // BROKEN PLATES
	NULL, // BROKEN GLASS
	NULL, // SHREDDED PAPER
	NULL, // BOOKS
	NULL, // BOOKS
	NULL, // A LETTER OPENER
	NULL, // A JACKET
	"THEY'RE HARDBACK RING BINDERS BULGING WITH TATTY BITS OF PAPER.", // NOTEBOOKS
	"THEY'RE PLANS OF THE CASTLE AND SHOW SECRET PASSAGES IN THE KITCHEN AND IN THE BEDROOMS.", // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
	"IT'S DINGLE'S.", // A BRIEFCASE
	"IT CONTAINS A VAST STAMP COLLECTION.", // A FOLDER
	"IT'S MADE OF CHINA.", // A PAPERWEIGHT
	"THERE ARE 10 ENVELOPES ALL MARKED 'EVIDENCE' YOU MUST FILL ALL OF THEM BEFORE YOU SOLVE THE MURDER. MOST EVIDENCE IS MARKED WITH AN #.", // PADDED ENVELOPES
	"JUST YOUR AVERAGE BOMB..", // A BOMB!
	NULL, // A SMALL KEY
	"SHOULD FIT A REVOLVER.", // BULLETS
	NULL, // SWORD
	NULL, // BALL ON CHAIN
	NULL, // HOURGLASS
	NULL, // GOLDEN SKULL
	NULL, // RED KEY
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	"IT'S MR. MCFUNGUS' SOUL!", // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY
};

const char* g_itemRead[MAX_ITEMS] =
{
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	"BRIEFLY, THE WILL LEAVES DONATIONS TO VARIOUS CHARITIES AND RELATIVES, $10000 TO COOK, THE PROFESSOR, THE MAJOR AND THE CHURCH. THE REST, WHICH COMES TO $1000000 IS LEFT TO GABRIEL GASBAG.", // THE WILL;
	NULL, // A KNIFE;
	"ITS THE MARRIAGES COLUMN OF 'THE TIMES'.", // NEWSPAPER CUTTING
	"A TYPED MESSAGE READS:\n\n10000 IS A SMALL FRACTION OF A MILLION.. YOU'LL NEVER HEAR FROM ME AGAIN.", // A NOTE;
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
	"IT READS:\n\nSAM WAS HERE.", // A PIECE OF CARD
	NULL, // A BRIEFCASE
	NULL, // A FOLDER
	NULL, // A PAPERWEIGHT
	NULL, // PADDED ENVELOPES
	NULL, // A BOMB!
	NULL, // A SMALL KEY
	NULL, // BULLETS
	"IT'S A MEDIEVAL SWORD.", // SWORD
	"IT'S A HEAVY BALL ON CHAIN WITH A HOOK.", // BALL ON CHAIN
	"IT'S AN ORDINARY LOOKING HOURGLASS.", // HOURGLASS
	"IT'S A SHINY 24 CARET GOLD SKULL WITH SWAROVSKI CRYSTALS.", // GOLDEN SKULL
	"IT'S A KEY WITH A STRANGE SCENT, SMELLS LIKE BLOOD!", // RED KEY
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEYa
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
	"THE LATE MR. MCFUNGUS' HEADSTONE",
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

const char* g_askAboutCharacter[MAX_CHARACTERS * MAX_CHARACTERS] =
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
	NULL,										// Bently
	"\"ER..YES.. A FINE COOK..\"",				// Cook
	NULL,										// Gabriel
	"\"MMM..FAR TOO SELF ASSURED.\"",			// Cynthia
	NULL,										// The Professor
	NULL,										// The Doctor
	"\"I THINK SOMEONE SHOULD PUT HIM OUT OF HIS MISERY!\"",	// The Major
	"\"DON'T BELIEVE A WORD HE SAYS.\"",			// Dingle
	"\"..YES, A MOST VALUABLE PARISHIONER..MAY HE REST IN PEACE.\"",	// Angus
	
	// Bentley
	NULL,										// Snide
	NULL,										// The Reverend
	NULL,										// Bently
	NULL,										// Cook
	NULL,										// Gabriel
	NULL,										// Cynthia
	NULL,										// The Professor
	NULL,										// The Doctor
	NULL,										// The Major
	NULL,										// Dingle
	"\"I FEEL IT WOULD BE IMPROPER, SIR, TO DISCUSS MY LATE EMPLOYER WITH A STRANGER..\"",	// Angus
	
	// Cook
	NULL,										// Snide
	NULL,										// The Reverend
	NULL,										// Bently
	NULL, 										// Cook
	NULL,										// Gabriel
	NULL,										// Cynthia
	NULL,										// The Professor
	NULL,										// The Doctor
	NULL,										// The Major
	NULL,										// Dingle
	"\"NOT MUCH TO SAY REALLY..OF COURSE HE WILL BE MISSED.\"",	// Angus

	// Gabriel
	NULL, 										// Snide
	"\"..I'VE HEARD HE MURDERED HIS WIFE..\"",	// The Reverend
	NULL,										// Bently
	"\"..WELL I THINK SHE'S IN LOVE..\"",		// Cook
	NULL, 										// Gabriel
	"\"SHE'S SO STUCK UP!\"",					// Cynthia
	"\"..OH HE'S A DEAR.\"",					// The Professor
	"\"I DON'T TRUST HIM!\"",					// The Doctor
	"\"..COMPLETELY MAD.\"",					// The Major
	NULL,										// Dingle
	"\"A GOOD MAN SIR, VERY GENEROUS..MADE A BIG DONATION TO THE CHURCH ROOF FUND, SO MAVIS BAGWORTHY SAYS.\"",	// Angus

	// Cynthia
	NULL,  										// Snide
	NULL,										// The Reverend
	NULL,										// Bently
	NULL,										// Cook
	NULL,										// Gabriel
	NULL, 										// Cynthia
	NULL,										// The Professor
	NULL,										// The Doctor
	NULL,										// The Major
	NULL,										// Dingle
	"\"SIMPLY AWFUL BUSINESS. I DIDN'T KNOW HIM, BUT PATER WAS TERRIBLY UPSET.\"",	// Angus

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
	"\"ER WHAT..OH YES..GREAT SHAME.. I HAD KNOWN HIM SINCE OXFORD.. POOR FELLOW HAD A TERRIBLE MEMORY FOR NUMBERS..\"",	// Angus

	// The Doctor
	NULL,  										// Snide
	NULL,										// The Reverend
	NULL,										// Bently
	NULL,										// Cook
	"\"BETWEEN YOU AND ME SHE HASN'T GOT TWO BRAIN CELLS TO RUB TOGETHER.\"",	// Gabriel
	NULL,										// Cynthia
	NULL,										// The Professor
	NULL, 										// The Doctor
	"\"HE CAN'T HAVE LONG LEFT.\"", 			// The Major
	NULL,										// Dingle
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
	"\"YES, DAMN SHAME.. POOR FELLOW ..\"",	// Angus

	// Dingle
	NULL, 										// Snide
	NULL,										// The Reverend
	NULL,										// Bently
	NULL,										// Cook
	NULL,										// Gabriel
	NULL,										// Cynthia
	NULL,										// The Professor
	NULL,										// The Doctor
	NULL, 										// The Major
	NULL, 										// Dingle
	"\"MOST TRAGIC. OF COURSE I AM NOT AT LIBERTY TO DISCUSS HIS BUSINESS AFFAIRS.\"",	// Angus
	
	// Angus
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
	"\"I'M TRAPPED HERE..\""					// Angus
};

const char* g_askAboutItem[MAX_ITEMS * MAX_CHARACTERS] =
{
	// Snide
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// The Reverend
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	"\"HAVE YOU BEEN SEARCHING MY ROOM, INSPECTOR?\"", // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Bentley

	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	"\"AHEM. I HAVE NOTHING TO SAY ABOUT THAT, SIR.\"", // A SOGGY ENVELOPE
	"\"AHEM. I HAVE NOTHING TO SAY ABOUT THAT, SIR.\"", // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	"\"PLEASE RETURN THAT PRIOR TO LEAVING, SIR.\"", // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	"\"IT WAS PRESENTED TO THE LATE MR. MCFUNGUS, SIR.\"", // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	"\"I CANNOT IMAGINE WHY YOU TOOK THAT, SIR.\"", // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	"\"IT WAS MR. MCFUNGUS' DIARY..\"", // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	"\"THAT BELONGS TO ME, SIR.\"", // A JACKET
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Cook
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	"\"I HAVE NEVER SEEN THAT BEFORE, INSPECTOR!\"", // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
	"\"JUST PUT THOSE BACK, PLEASE. I'LL GET AROUND TO THEM.\"", // DIRTY PLATES
	NULL, // A PICTURE
	NULL, // A WAD OF NOTES
	NULL, // A LOCKET
	NULL, // A SCREWDRIVER
	NULL, // AN OPEN LOCKET
	"\"MR. MCFUNGUS WAS VERY FOND OF THOSE PLATES, INSPECTOR.\"", // BROKEN PLATES
	NULL, // BROKEN GLASS
	NULL, // SHREDDED PAPER
	NULL, // BOOKS
	NULL, // BOOKS
	NULL, // A LETTER OPENER
	NULL, // A JACKET
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Gabriel
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Cynthia
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	"\"WHAT ARE YOU DOING WITH MY MIRROR?\"", // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// The Professor
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	"\"..YES, THIS BOOK..ANGUS SAID..I THINK..WHAT WAS THAT?\"", // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	"\".. THAT REMINDS ME..ANGUS ONCE TOLD ME SOMETHING ABOUT A BOOK..ONE HUNDRED AND ONE DETECTIVE STORIES OR SOMETHING..\"", // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// The Doctor
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	"\"YOU'D BETTER PUT THAT BACK WHERE YOU FOUND IT, INSPECTOR..\"", // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	"\"MY SCALPELS! WHERE DID YOU FIND THEM?\"", // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	"\"THAT'S MY BAG, INSPECTOR.\"", // A BLACK BAG
	"\"THAT'S THE SAME BRAND I USE.\"", // COLOGNE
	NULL, // A SMALL BOOK
	NULL, // DIRTY PLATES
	NULL, // A PICTURE
	"\"YES, WHAT ABOUT IT? MEDICINE PAYS, INSPECTOR.\"", // A WAD OF NOTES
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// The Major
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Dingle
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	"\"IT'S THE WILL.\"", // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	"\"OBVIOUSLY A FAKED WILL..WHERE DID YOU FIND IT?\"", // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
	"\"YES, IT'S MY BRIEFCASE. WHY DID YOU TAKE IT?\"", // A BRIEFCASE
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY

	// Angus
	
	NULL,
	NULL, // A HOT WATER BOTTLE
	NULL, // BLANK BULLETS
	NULL, // A CANDLESTICK
	NULL, // THE WILL;
	NULL, // A KNIFE;
	NULL, // NEWSPAPER CUTTING
	NULL, // A NOTE;
	NULL, // A SMALL BOTTLE
	NULL, // A CRAVATE;
	NULL, // A SOGGY ENVELOPE
	NULL, // A LETTER
	NULL, // SCALPELS
	NULL, // A SYRINGE;
	NULL, // A BOTTLE OF PILLS
	NULL, // A HAMMER
	NULL, // A BUNCH OF KEYS
	NULL, // A BIG IRON KEY
	NULL, // A SILVER TRAY
	NULL, // A BOTTLE OF WINE
	NULL, // A COMB
	NULL, // A HARDBACK BOOK
	NULL, // A FOLDED DOCUMENT;
	NULL, // AN ELEPHANT GUN
	NULL, // A DIARY
	NULL, // A BLACK BAG
	NULL, // COLOGNE
	NULL, // A SMALL BOOK
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
	NULL, // NOTEBOOKS
	NULL, // PLANS
	NULL, // A MIRROR
	NULL, // CUTLERY
	NULL, // A PIECE OF CARD
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
	NULL, // VACUUM CLEANER
	NULL, // WASHING POWDER
	NULL, // DIRTY SHIRT
	NULL, // ANGUS MCFUNGUS
	NULL, // A HIDDEN KEY
};

const char* g_askAboutProfessorRandom[] =
{
	"\"..OH YES..HOW ABOUT YOU?\"",
	"\"..NO..NO..IT'S BISMUTH.\"",
	"\"..HALF PAST NINE.\"",
	"\"CAN YOU SMELL THAT, SNIDE?\"",
	"\"SORRY, WHAT WAS THAT?\""
};

const char* g_askAboutMajorRandom[] =
{
	"\"..DIRTY RATS..\" MUMBLES THE MAJOR.",
	"THE MAJOR GRUMBLES \"OUGHT TO BE SHOT.\"",
	"THE MAJOR BABBLES INCOMPREHENSIBLY..",
	"\"GRENADE!\" SHOUTS THE MAJOR."
};

const char* g_iconName[] =
{
	"           ",
	"    OPEN   ",
	"  EXAMINE  ",
	" INVENTORY ",
	"    DROP   ",
	"    SAVE   ",
	"    LOAD   ",
	"   SHOOT   ",
	"   ACCUSE  ",
	" OPEN DOOR ",
	"CLOSE DOOR ",
	"  USE KEY  ",
	" QUESTION  ",
	"    READ   ",
	"  CONSUME  ",
	"    USE    ",
	"   PAUSE   ",
	"   PUT IN  ",
	"   VACUUM  "
};

const char* g_roomName[MAX_ROOMS] =
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
	"LAUNDRY",
	"GARDEN",
	"GRAVEYARD",
	"COURTYARD",
	"MR. MCFUNGUS' LANDING",
	"MR. MCFUNGUS' ROOM",
	"MR. MCFUNGUS' SECRET ROOM",
	"MR. MCFUNGUS' STAIRS",
	"DINING ROOM",
	"SEWERS"
};

const char* g_enterRoomText[MAX_ROOMS] =
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
	NULL,									// Outside 1
	NULL,									// Outside 2
	NULL,									// Outside 3
	NULL,									// Outside 4
	"YOU ARE OUTSIDE.",						// Passage 1
	NULL,									// Passage 2
	NULL,									// Passage 3
	NULL,									// Hall 1
	NULL,									// Hall 2
	NULL,									// Hall 3
	NULL,									// Hall 4
	"YOU ARE ON THE LANDING.",
	"YOU ARE IN THE KITCHEN.",
	"YOU ARE IN THE HALL.",
	"YOU ARE IN THE STUDY.",
	NULL,									// Clock
	"YOU ARE IN THE CELLAR.",
	"YOU ARE IN THE DRAWING ROOM.",
	"YOU ARE IN THE LIBRARY.",
	"YOU ARE IN THE LAUNDRY.",
	"YOU ARE IN THE GARDEN.",
	"YOU ARE IN HE GRAVEYARD.",
	"YOU ARE IN THE COURTYARD.",
	"YOU ARE ON MR. MCFUNGUS' LANDING.",
	"YOU ARE IN MR. MCFUNGUS' ROOM.",
	"YOU ARE IN MR. MCFUNGUS' SECRET ROOM.",
	"YOU ARE ON MR. MCFUNGUS' STAIRCASE.",
	"YOU ARE IN THE DINING ROOM.",
	"YOU ARE IN THE SEWERS."
};

const char* g_saveName[] =
{
	"/Data/TDG/Data/Save01.dat",
	"/Data/TDG/Data/Save02.dat",
	"/Data/TDG/Data/Save03.dat",
	"/Data/TDG/Data/Save04.dat",
	"/Data/TDG/Data/Save05.dat"
};

const char* g_keyboardText[] =
{
	"    1 2 3 4 5 6 7 8 9 0 EXIT    ",
	"                                ",
	"    Q W E R T Y U I O P BKSP    ",
	"                                ",
	"     A S D F G H J K L ENTER    ",
	"                                ",
	"      Z X C V B N M  SPACE      "
};

const char* g_keyboardHit[] =
{
	"\000\000\000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\000\e\e\e\e\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000Q\000W\000E\000R\000T\000Y\000U\000I\000O\000P\000\b\b\b\b\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000\000A\000S\000D\000F\000G\000H\000J\000K\000L\000\n\n\n\n\n\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
	"\000\000\000\000\000\000Z\000X\000C\000V\000B\000N\000M\000       \000\000\000\000\000",
	"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
};

const int g_largeTextMap[] =
{
	0x00,0x20,0x22,0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x1C,0x1F,0x1B,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0x1E,0x00,0x00,0x00,0x21,
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x00,0x00,0x00,0x00,0x00,
	0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void DrawChar(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = c - 0x20;
}

void DrawString(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(int i=0; i<(int)strlen(string); i++)
		*pMap++ = string[i] - 0x20;
}

void DrawString(const char* string, int x, int y, int count, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(int i=0; i<(int)strlen(string) && i < count; i++)
		*pMap++ = string[i] - 0x20;
}

void DrawStringLarge(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(int i=0; i<(int)strlen(string); i++)
	{	
		*pMap = 96 + g_largeTextMap[string[i] - 0x20] * 2;
		*(pMap+32) = 96 + g_largeTextMap[string[i] - 0x20] * 2 + 1;
		pMap++;
	}
}

void DrawCharLarge(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = 96 + g_largeTextMap[c - 0x20] * 2;
	*(pMap+32) = 96 + g_largeTextMap[c - 0x20] * 2 + 1;
}

