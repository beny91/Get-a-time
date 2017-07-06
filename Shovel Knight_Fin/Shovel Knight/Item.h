#pragma once
#include "obj.h"

class CItem :
	public CObj
{
protected:
	int m_DeadTime;
	int m_iPrice;

public:
	virtual void Initialize(void);
	virtual int	 Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CItem(void);
	CItem(string strName, float fx, float fy, float fcx, float fcy ,int _price=0, int Hp =0, int Mp =0, int Att =10 );
	~CItem(void);
};
