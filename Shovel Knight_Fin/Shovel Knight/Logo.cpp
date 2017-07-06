#include "StdAfx.h"
#include "Logo.h"
#include "SceneMgr.h"

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Initialize(void)
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Video/ShovelKnight.wmv");

	m_time=150;
	MoveWindow(m_hVideo, 0, 0, g_iWINCX, g_iWINCY, NULL);
	MCIWndPlay(m_hVideo);
}

int CLogo::Progress(void)
{
	if(m_time < 0)
	{
		 MCIWndStop(m_hVideo);
		 CSceneMgr::GetInstance()->SetChangeScene(SCENE_GAMEMENU);
	}
	if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SetChangeScene(SCENE_GAMEMENU);
	}
	m_time--;
	return 0;
}

void CLogo::Render(HDC _hdc)
{

}

void CLogo::Release(void)
{
	MCIWndClose(m_hVideo);
	MCIWndDestroy(m_hVideo);
}
