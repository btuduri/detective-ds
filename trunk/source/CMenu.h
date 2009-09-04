#ifndef __CMENU_H__
#define __CMENU_H__

#include "TDG.h"

#define MAX_ICONS				9

enum IconType
{
	ICON_NOTHING,
	ICON_OPEN,
	ICON_EXAMINE,
	ICON_INVENTORY,
	ICON_DROP,
	ICON_SAVE,
	ICON_LOAD,
	ICON_SHOOT,
	ICON_ACCUSE,
	ICON_DOOR_OPEN,
	ICON_DOOR_CLOSE,
	ICON_USE_KEY,
	ICON_QUESTION,
	ICON_READ,
	ICON_CONSUME,
	ICON_USE,
	ICON_TIME,
	ICON_PLACE,
	ICON_BAG
};

class CMenu
{
public:
	CMenu();
	~CMenu();
	
	void DrawIcon(IconType iconType, int x, int y, bool sub);

private:
	IconType m_iconArray[MAX_ICONS];
};

#endif
