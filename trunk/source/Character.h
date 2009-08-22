#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"

#define MAX_CHARACTERS			10

#define CHARACTER_WIDTH			24
#define CHARACTER_HEIGHT		41

#define HEAD_HEIGHT				21

enum CharacterType
{
	CHARACTER_SNIDE,
	CHARACTER_REVEREND,
	CHARACTER_BENTLEY,
	CHARACTER_COOK,
	CHARACTER_GABRIEL,
	CHARACTER_CYNTHIA,
	CHARACTER_PROFESSOR,
	CHARACTER_DOCTOR,
	CHARACTER_MAJOR,
	CHARACTER_DINGLE
};

class CCharacter
{
public:
	CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite);
	~CCharacter();
	
	void SetPosition(int x, int y);
	void SetPriority(int index);
	void Animate(int elapsedTime);
	void Hide();
	void Draw();
	void Face(DirectionType directionType);
	void Move(DirectionType directionType);
	
	void SetFrameType(FrameType frameType);
	
	int X() const { return m_x; }
	int Y() const { return m_y; }
	
	int Priority() const { return m_pHeadSprite->OamIndex(); }

private:
	CharacterType m_characterType;
	CSprite* m_pHeadSprite;
	CSprite* m_pBodySprite;
	
	int m_x;
	int m_y;
};

#endif