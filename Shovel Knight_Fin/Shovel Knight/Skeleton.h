#pragma once
#include "monster.h"
#include "Define.h"
class CTreasure;
class CSkeleton :
	public CMonster
{
private:
	CObj* m_pTreasure;
private:
	void MovePattern(void);
	void FrameCheck(void);
	void KeyCheck(void);
	void DeadCheck(void);
	void CreateAttackBox(void);
	void CreateTreasure(void);
private:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CSkeleton(void);
	CSkeleton(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CSkeleton(void);
};
