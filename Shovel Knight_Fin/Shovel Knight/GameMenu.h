#pragma once
#include "scene.h"

class CObj;

class CGameMenu :
	public CScene
{
private:
	CObj* m_pCurSor;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
public:
	CGameMenu(void);
	virtual ~CGameMenu(void);
};
