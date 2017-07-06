#pragma once

#include "Define.h"

class CMainGame
{
private:
	HDC		m_HDC;

	DWORD m_dwTime;
	TCHAR m_szFPS[128];
	int   m_iFPS;
private:
	void FPS_CHECK(void);

public:
	void Initialize(void);
	int Progress(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
