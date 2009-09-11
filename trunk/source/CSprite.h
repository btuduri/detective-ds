#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include <nds.h>

#define MAX_SPRITES		24

enum FrameType
{
	FRAME_NONE = 0,
	FRAME_WAITING = BIT(0),
	FRAME_SPEAK = BIT(1),
	FRAME_LEFT = BIT(2),
	FRAME_RIGHT = BIT(3),
	FRAME_UP = BIT(4),
	FRAME_DOWN = BIT(5),
	FRAME_DEAD = BIT(6),
	FRAME_BOMB = BIT(7),
	FRAME_GREEN_SPEAK = BIT(8),
	FRAME_GREEN_LEFT = BIT(9),
	FRAME_GREEN_RIGHT = BIT(10),
	FRAME_GREEN_UP = BIT(11),
	FRAME_GREEN_DOWN = BIT(12),
	FRAME_MAGNIFYER = BIT(13),
	FRAME_ARROW = BIT(14)
};

enum SpriteType
{
	SPRITE_SNIDE_HEAD,
	SPRITE_SNIDE_BODY,
	SPRITE_REVEREND_HEAD,
	SPRITE_REVEREND_BODY,
	SPRITE_BENTLEY_HEAD,
	SPRITE_BENTLEY_BODY,
	SPRITE_COOK_HEAD,
	SPRITE_COOK_BODY,
	SPRITE_GABRIEL_HEAD,
	SPRITE_GABRIEL_BODY,
	SPRITE_CYNTHIA_HEAD,
	SPRITE_CYNTHIA_BODY,
	SPRITE_PROFESSOR_HEAD,
	SPRITE_PROFESSOR_BODY,
	SPRITE_DOCTOR_HEAD,
	SPRITE_DOCTOR_BODY,
	SPRITE_MAJOR_HEAD,
	SPRITE_MAJOR_BODY,
	SPRITE_DINGLE_HEAD,
	SPRITE_DINGLE_BODY,
	SPRITE_ANGUS_HEAD,
	SPRITE_ANGUS_BODY,
	SPRITE_COL1,
	SPRITE_COL2
};

class CSprite
{
public:
	CSprite(SpriteType spriteType, const u32* pBmp, const u32* frameArray, int frameCount);
	//CSprite(SpriteType spriteType, const u32* pTiles, int tilesLen, const u16* pPalette, int paletteLen, const int* frameArray, int frameCount);
	~CSprite();
	
	void SetPosition(int x, int y);
	void Animate(int elapsedTime);
	void Hide();
	void Draw();
	void SetFrameType(FrameType frameType);
	
	void SetOamIndex(int oamIndex) { m_oamIndex = oamIndex; }
	int OamIndex() const { return m_oamIndex; }
	
	void SetAlpha(int alpha) { m_alpha = alpha; }
	
	void SetPriority(int priority) { m_priority = priority; }
	int Priority() const { return m_priority; }
	
	int X() const { return m_x; }
	int Y() const { return m_y; }

private:
	SpriteType m_spriteType;
	const u32* m_pBmp;
	//const u32* m_pTiles;
	//const u16* m_pPalette;
	
	//int m_tilesLen;
	//int m_paletteLen;
	
	const u32* m_frameArray;
	FrameType m_frameType;
	int m_frameNum;
	int m_frameCount;
	int m_lastUpdate;
	
	int m_oamIndex;
	int m_priority;
	
	u16* m_gfxMain;
	u16* m_gfxSub;
	
	int m_x;
	int m_y;
	
	int m_alpha;
};

#endif