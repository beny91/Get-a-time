#pragma once
#include "monster.h"
#include "Define.h"

class CTreasure;
class CBeeto :
	public CMonster
{
private:
	CObj* m_pTreasure;
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
	CBeeto(void);
	CBeeto(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CBeeto(void);
};
