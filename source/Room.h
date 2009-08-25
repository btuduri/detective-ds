#ifndef __CROOM_H__
#define __CROOM_H__

#include "TDG.h"

#define MAX_ROOMS			30
#define MAX_DOORS			10

#define ROOM_FLOOR_TOP		144
#define ROOM_FLOOR_BOTTOM	184
#define ROOM_HORIZ_CENTRE	128
#define ROOM_VERT_CENTRE	168

enum RoomType
{
	ROOM_SNIDE,
	ROOM_REVEREND,
	ROOM_BENTLEY,
	ROOM_COOK,
	ROOM_GABRIEL,
	ROOM_CYNTHIA,
	ROOM_PROFESSOR,
	ROOM_DOCTOR,
	ROOM_MAJOR,
	ROOM_DINGLE,
	ROOM_OUTSIDE1,
	ROOM_OUTSIDE2,
	ROOM_OUTSIDE3,
	ROOM_OUTSIDE4,
	ROOM_OUTSIDE5,
	ROOM_PASSAGE1,
	ROOM_PASSAGE2,
	ROOM_PASSAGE3,
	ROOM_HALL1,
	ROOM_HALL2,
	ROOM_HALL3,
	ROOM_HALL4,
	ROOM_LANDING,
	ROOM_KITCHEN,
	ROOM_STAIRS,
	ROOM_STUDY,
	ROOM_CLOCK,
	ROOM_CELLAR,
	ROOM_DRAWING,
	ROOM_LIBRARY
};

class CDoor;

class CRoom
{
public:
	CRoom(RoomType roomType, CMap* pMap, const unsigned char* colMap);
	~CRoom();
	
	void Initialize(int x);
	void Draw();
	bool Scroll(DirectionType directionType);
	
	void SetDoor(int doorType, CDoor* pDoor) { m_doorArray[doorType] = pDoor; }
	CDoor* GetDoor(int doorType) const { return m_doorArray[doorType]; }
	
	void SetX(int x) { m_pMap->SetX(x); }
	void SetY(int y) { m_pMap->SetY(y); }

	CMap* pMap() const { return m_pMap; }	
	int X() const { return m_pMap->X(); }
	int Y() const { return m_pMap->Y(); }
	int Width() const { return m_pMap->Width(); }
	int Height() const { return m_pMap->Height(); }
	u8 ColMap(int x, int y) const { return (m_colMap == NULL ? 0 : *(m_colMap + x + y * (m_pMap->Width() / 8))); }

private:
	RoomType m_roomType;
	CMap* m_pMap;
	const u8* m_colMap;
	
	CDoor* m_doorArray[MAX_DOORS];
};

#endif