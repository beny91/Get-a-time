#include "StdAfx.h"
#include "GameMenu.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "Obj.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "CourSour.h"

CGameMenu::CGameMenu(void)
{
}

CGameMenu::~CGameMenu(void)
{
	Release();
}

void CGameMenu::Initialize(void)
{
	CObj::SetBitBmp(&m_mapBmp);

	

	m_mapBmp.insert( make_pair("TITLE", (new CBitBmp)->LoadBmp(L"../Resource/menu/title.bmp") ) );
	m_mapBmp.insert( make_pair("CURSOR", (new CBitBmp)->LoadBmp(L"../Resource/menu/Cursor.bmp") ) );
	m_mapBmp.insert( make_pair("BACK_BUFFER", (new CBitBmp)->LoadBmp(L"../Resource/menu/title.bmp") ) );
	
	m_pCurSor = new CCourSour("CURSOR",300,360,100,21);
	m_pCurSor->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pCurSor,OBJ_CURSOR);

	char  szTemp[128];		//재생.
	TCHAR szTemp2[128];		//재생.strcpy(szTemp2, L"Shovel Knight OST - Strike the Earth! Plains of Passage");

	CSoundMgr::GetInstance()->PlayBGMSound(L"Shovel Knight OST - Main Theme.mp3");
}

int CGameMenu::Progress(void)
{
	/*if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SetScene(SCENE_STAGE);
	}*/

	//for(list<CObj*>::iterator iter = m_listButton.begin();
	//	iter != m_listButton.end(); ++iter)
	//{
	//	int iResult = (*iter)->Progress();

	//	if(iResult == 1)
	//	{
	//		CSceneMgr::GetInstance()->SetChangeScene(SCENE_STAGE);
	//		//return 1;
	//	}
	//	else if(iResult == 2)
	//	{
	//		CSceneMgr::GetInstance()->SetChangeScene(SCENE_EDIT);
	//		//return 1;
	//	}
	//}
	CObjMgr::GetInstance()->Progress();
	
	return 0;
}

void CGameMenu::Render(HDC _hdc)
{
	

	BitBlt(m_mapBmp["BACK_BUFFER"]->GetMemDC(), 
		0, 0, 
		800, 600,
		m_mapBmp["TITLE"]->GetMemDC(),
		0,0,
		SRCCOPY);
	CObjMgr::GetInstance()->Render(m_mapBmp["BACK_BUFFER"]->GetMemDC());

	
	BitBlt(_hdc, 
		CObj::m_ptScroll.x, 0, 
		800, 600,
		m_mapBmp["BACK_BUFFER"]->GetMemDC(),
		0,0,
		SRCCOPY);
}

void CGameMenu::Release(void)
{
	CSoundMgr::GetInstance()->StopBGM();

	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_CURSOR].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_CURSOR].end();

	for( iter ; iter != iter_end; ++iter)
	{
		delete (*iter);
	}
	CObjMgr::GetInstance()->GetList()[OBJ_CURSOR].clear();
	CObjMgr::GetInstance()->Destroy();
}
