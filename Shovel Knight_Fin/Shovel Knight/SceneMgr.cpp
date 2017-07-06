#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameMenu.h"
#include "Stage.h"
#include "MapEdit.h"
#include "Logo.h"


INIT_SINGLTONE(CSceneMgr)

CSceneMgr::CSceneMgr(void)
:m_pScene(NULL)
,m_bChangeScene(false)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::Initialize(void)
{
	
}

int CSceneMgr::Progress(void)
{
	if(m_bChangeScene)
	{
		m_bChangeScene = false;
		SetScene(m_eType);
	}

	if(m_pScene)
		m_pScene->Progress();

	return 0;
}

void CSceneMgr::Render(HDC _hdc)
{
	if(m_pScene)
		m_pScene->Render(_hdc);
}

void CSceneMgr::Release(void)
{
	SAFE_DELETE(m_pScene);
}

void CSceneMgr::SetScene(eSCENE_TYPE eType)
{
	SAFE_DELETE(m_pScene);

	//if(m_pScene)
	//{
		//값을 지우자.
	//}
	
	switch(eType)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;
	case SCENE_GAMEMENU:
		m_pScene = new CGameMenu;
		break;

	case SCENE_STAGE:
		m_pScene = new CStage;
		break;

	case SCENE_EDIT:
		m_pScene = new CMapEdit;
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::SetChangeScene(eSCENE_TYPE eType)
{
	m_eType = eType;

	m_bChangeScene = true;
}
