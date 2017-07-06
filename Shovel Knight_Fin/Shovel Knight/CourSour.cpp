#include "StdAfx.h"
#include "CourSour.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CCourSour::CCourSour(void)
{
}

CCourSour::~CCourSour(void)
{
}

CCourSour::CCourSour(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:CObj(strName,fx,fy,fcx,fcy, Hp, Mp, Att)
{

}

void CCourSour::Initialize(void)
{
	m_tFrame = FRAME(0,2,0,300);
	m_dwFrameTime = GetTickCount();


}
int	 CCourSour::Progress(void)
{
	KeyCheck();
	FrameMove(STATE_STAND,0,2,0,300);
	return 0;
}
void CCourSour::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 ),
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2),
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//빼고 싶은 색.s
}
void CCourSour::Release(void)
{
}

void CCourSour::KeyCheck(void)
{
	if(GetAsyncKeyState(VK_UP)  )
	{
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_menu_file_cursor_move.mp3");
		m_tInfo.m_fY -=40;
	}

	if(GetAsyncKeyState(VK_DOWN) )
	{
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_menu_file_cursor_move.mp3");
		m_tInfo.m_fY +=40;
	}

	if( m_tInfo.m_fY >400)
		m_tInfo.m_fY =360;

	if( m_tInfo.m_fY <360)
		m_tInfo.m_fY= 400;

	if(GetAsyncKeyState(VK_RETURN) & 1)
	{
		CSoundMgr::GetInstance()->PlayEffectSound(L"sfx_menu_file_confirm.mp3");
		if(m_tInfo.m_fY ==360)
			CSceneMgr::GetInstance()->SetChangeScene(SCENE_STAGE);
		else
			CSceneMgr::GetInstance()->SetChangeScene(SCENE_EDIT);
	}
}