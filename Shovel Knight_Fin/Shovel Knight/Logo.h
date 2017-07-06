#pragma once
#include "scene.h"

class CLogo :
	public CScene
{
private:
	HWND		m_hVideo;
	int m_time;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CLogo(void);
	virtual ~CLogo(void);
};
