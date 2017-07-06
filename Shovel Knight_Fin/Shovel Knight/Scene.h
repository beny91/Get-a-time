#pragma once

#include "Define.h"

class CBitBmp;

class CScene
{
protected:
	map<string, CBitBmp*>	m_mapBmp;


public:
	virtual void Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};
