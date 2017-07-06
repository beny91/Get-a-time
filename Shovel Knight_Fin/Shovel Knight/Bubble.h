#pragma once
#include "monster.h"

class CBubble :
	public CMonster
{
private:
	int m_min;
	int m_max;
	int m_iType;
public:
	void SetType(int _type) {m_iType = _type;};
public:
	int GetType(void) {return m_iType;};
private:
	void MovePattern(void);
	void FrameCheck(void);
	void KeyCheck(void);
	void DeadCheck(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CBubble(void);
	CBubble(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CBubble(void);
};
