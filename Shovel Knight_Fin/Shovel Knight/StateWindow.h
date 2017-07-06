#pragma once
#include "ui.h"

class CMyFont;

class CStateWindow :
	public CUi
{
private:

	CMyFont* m_ArrayMoney[4];
	CMyFont* m_ArrayMp[2];
	CMyFont* m_LifePoint[4];
	CMyFont* m_BossLifePoint[4];



public:
	void Money(void);
	void Mp(void);
	void Life(void);
	void QickSkill(void);
	void BossLife(void);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CStateWindow(void);
	CStateWindow(string strName, float fx, float fy, float fcx, float fcy);
	virtual ~CStateWindow(void);
};
