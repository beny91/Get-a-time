#pragma once
#include "obj.h"

class CCourSour :
	public CObj
{
private:
		void KeyCheck(void);
private:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CCourSour(void);
	CCourSour(string strName, float fx, float fy, float fcx, float fcy , int Hp =0, int Mp =0, int Att =10 );
	~CCourSour(void);
};
