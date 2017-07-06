#pragma once
#include "monster.h"

class CBubble;
class CTreasure;
class CBubbleDragon :
	public CMonster
{
private:
	CObj* m_pBubble;
	CObj* m_pTreasure;
	int m_Dealay;
	int m_max;
	int m_min;
private:
	void MovePattern(void);
	void FrameCheck(void);
	void KeyCheck(void);
	void DeadCheck(void);
	void CreateTreasure(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CBubbleDragon(void);
	CBubbleDragon(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10  );
	virtual ~CBubbleDragon(void);
};
