#pragma once
#include "monster.h"
#include "Define.h"
class CBlorb :
	public CMonster
{
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CBlorb(void);
	CBlorb(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	virtual ~CBlorb(void);
};
