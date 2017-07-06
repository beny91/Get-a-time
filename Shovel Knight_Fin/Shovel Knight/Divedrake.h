#pragma once
#include "monster.h"
#include "Define.h"
class CDivedrake :
	public CMonster
{
private:
	int m_iPattern;
	float m_angle;
public:
	void SetPattern(int _pattern) {m_iPattern = _pattern;};
private:
	void MovePattern(void);
	void FrameCheck(void);
	void KeyCheck(void);
	void DeadCheck(void);
private:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CDivedrake(void);
	CDivedrake(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10  );
	virtual ~CDivedrake(void);
};
