#pragma once
#include "obj.h"

class COtherObj :
	public CObj
{
protected:
	int m_DeadTime;
public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	COtherObj(void);
	COtherObj(string strName, float fx, float fy, float fcx, float fcy , int Hp =10, int Mp =0, int Att =10 );
	~COtherObj(void);
};
