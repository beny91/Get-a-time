#include "StdAfx.h"
#include "StateWindow.h"
#include "ObjMgr.h"
#include "MyFont.h"
#include "Player.h"




CStateWindow::CStateWindow(void)
{
}

CStateWindow::CStateWindow(string strName, float fx, float fy, float fcx, float fcy)
:CUi(strName, fx, fy, fcx, fcy)
{

}

CStateWindow::~CStateWindow(void)
{
	Release();
}

void CStateWindow::Initialize(void)
{
	//money 숫자
	for( int i = 0 ; i < 4; ++i)
	{
		m_ArrayMoney[i] = new CMyFont("NUMBER",static_cast<float>(25+(i*25)),25,25,25);
		m_ArrayMoney[i]->Initialize();
		m_ArrayMoney[i]->SetPosition(4-i); //1의자리부터 1000의 자리까지 설정하는 값.
	}
	//mana 숫자
	for( int i = 0 ; i < 2; ++i)
	{
		m_ArrayMp[i] = new CMyFont("NUMBER",static_cast<float>(220+(i*25)),25,25,25);
		m_ArrayMp[i]->Initialize();
		m_ArrayMp[i]->SetPosition(2-i);
	}
	//life 숫자
	for( int i = 0 ; i < 4; ++i)
	{
		m_LifePoint[i] = new CMyFont("PLAYER_LIFE",static_cast<float>(320+(i*25)),25,21,21);
		m_LifePoint[i]->Initialize();
		m_LifePoint[i]->SetLifePos(i+1);
	}

	for( int i = 0 ; i < 4; ++i)
	{
		m_BossLifePoint[i] = new CMyFont("BOSS_LIFE",static_cast<float>(650+(i*25)),25,21,21);
		m_BossLifePoint[i]->Initialize();
		m_BossLifePoint[i]->SetLifePos(i+1);
	}
	
	
	
}
int CStateWindow::Progress(void)
{
	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	OBJ_ITER iter_boss = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();

	for( int i = 0 ; i < 4; ++i)
	{
		m_ArrayMoney[i]->SetNumber((*iter)->GetMoney() );
		m_ArrayMoney[i]->Progress();
	}
	
	for( int i = 0 ; i < 2; ++i)
	{
		m_ArrayMp[i]->SetNumber( (*iter)->GetMp() );
		m_ArrayMp[i]->Progress();
	}

	for( int i = 0 ; i < 4; ++i)
	{
		m_LifePoint[i]->SetNumber(  (*iter)->GetHp() );
		m_LifePoint[i]->Progress();
	}

	for( int i = 0 ; i < 4; ++i)
	{
		m_BossLifePoint[i]->SetNumber( (*iter_boss)->GetHp());
		m_BossLifePoint[i]->Progress();
	}

	return 0;
}
void CStateWindow::Render(HDC _hdc)
{
	BitBlt(_hdc, 
		static_cast<int>(m_tInfo.m_fX  ),
		static_cast<int>(m_tInfo.m_fY),
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName.data()]->GetMemDC(),
		0, // 이미지의 x
		0, // 이미지의 y
		SRCCOPY);	

	for( int i = 0 ; i < 4 ; ++i)
	{
		m_ArrayMoney[i]->Render(_hdc);
	}

	for( int i = 0 ; i < 2 ; ++i)
	{
		m_ArrayMp[i]->Render(_hdc);
	}
	for( int i = 0 ; i < 4; ++i)
	{
		m_LifePoint[i]->Render(_hdc);
	}

	for( int i = 0 ; i < 4; ++i)
	{
		m_BossLifePoint[i]->Render(_hdc);
	}

	
	/*m_LifePoint->Render( (*m_mapBmp)[m_LifePoint->GetName()]->GetMemDC());
	m_BossLifePoint->Render( (*m_mapBmp)[m_BossLifePoint->GetName()]->GetMemDC());*/

}

void CStateWindow::Release(void)
{
	for( int i = 0; i < 5 ; ++i)
	{
		SAFE_DELETE(m_ArrayMoney[i]);
	}

	for( int i = 0 ; i < 2 ; ++i)
	{
		SAFE_DELETE(m_ArrayMp[i]);
	}

	for( int i = 0; i < 4 ; ++i)
	{
		SAFE_DELETE(m_LifePoint[i]);
	}

	for( int i = 0; i < 6 ; ++i)
	{
		SAFE_DELETE(m_BossLifePoint[i]);
	}


}

void CStateWindow::Money(void)
{

}
void CStateWindow::Mp(void)
{

}
void CStateWindow::Life(void)
{

}
void CStateWindow::QickSkill(void)
{

}
void CStateWindow::BossLife(void)
{

}