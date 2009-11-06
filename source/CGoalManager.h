#ifndef __CGOALMANAGER_H__
#define __CGOALMANAGER_H__

#include <stdio.h>
#include "CRoom.h"
#include "CGoal.h"
#include "Text.h"

#define MAX_GOALS		64

class CGoalManager
{
public:
	CGoalManager();
	~CGoalManager();
	
	void ClearGoals();
	bool AddGoal(CGoal* pGoal);
	bool InsertGoal(CGoal* pGoal);
	bool RemoveGoal(CGoal* pGoal);
	void ResetGoals();
	
	void SetGoalPosition(int value) { m_goalPosition = value; }
	
	CGoal* CurrentGoal() const { return m_goalArray[m_goalPosition]; }
	void NextGoal();
	
private:

	CGoal* m_goalArray[MAX_GOALS];
	int m_goalPosition;
};

#endif