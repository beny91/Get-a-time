#include "StdAfx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame(void)
{
	m_HDC = GetDC(g_hWnd);

	m_dwTime	= GetTickCount();
	lstrcpy(m_szFPS, L"");		//m_szFPS		= L"";
	m_iFPS		= 0;


#ifdef _DEBUG_TYPE_
	AllocConsole(); 
	freopen( "CONOUT$",  "wt", stdout);
	SetConsoleTitleA("Debug");
#endif
}

CMainGame::~CMainGame(void)
{
	Release();
#ifdef _DEBUG_TYPE_
	FreeConsole();
#endif
}

void CMainGame::Initialize(void)
{
		CSoundMgr::GetInstance()->LoadSoundFile();
	m_HDC = GetDC(g_hWnd);


	CSceneMgr::GetInstance()->Initialize();
	CSceneMgr::GetInstance()->SetChangeScene(SCENE_LOGO);
	//CSceneMgr::GetInstance()->SetChangeScene(SCENE_STAGE);
	//CSceneMgr::GetInstance()->SetChangeScene(SCENE_EDIT);
}

int CMainGame::Progress(void)
{
	//마우스값.
	CMouse::SetMousePos();

	//키보드값.
	CKeyMgr::GetInstance()->SetKeyState();
	
	CSceneMgr::GetInstance()->Progress();

	return 0;
}

void CMainGame::Render(void)
{
	
	FPS_CHECK();
	CSceneMgr::GetInstance()->Render(m_HDC);
}

void CMainGame::Release(void)
{
	CObjMgr::GetInstance()->Destroy();
}


void CMainGame::FPS_CHECK(void)
{
	if(m_dwTime + 1000 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
	}

	++m_iFPS;
}