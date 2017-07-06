#include "StdAfx.h"
#include "Bord.h"

CBord::CBord(void)
{
}

CBord::CBord(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:COtherObj(strName,fx,fy,fcx,fcy, Hp , Mp , Att)
{

}

CBord::~CBord(void)
{
}

void CBord::Initialize(void)
{
	m_tFrame = FRAME(0,0,0,100);//프레임 초기화
	m_bDeadCheck=false;
	m_DeadTime=10;
	m_dwFrameTime=GetTickCount();
	m_eDir=DIR_LEFT;
	m_min=m_tInfo.m_fX-100 ;
	m_max=m_tInfo.m_fX+100;
	
	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, m_tInfo.m_fCY);
}
int	 CBord::Progress(void)
{
	Move();
	FrameCheck();
	return 0;
}
void CBord::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//빼고 싶은 색.s
}
void CBord::Release(void)
{
}

void CBord::FrameCheck(void)
{
	FrameMove(STATE_STAND,0,0,0,200);
}
void CBord::Move(void)
{
	

	if( m_tInfo.m_fX <m_min)
	{
		m_eDir=DIR_RIGHT;
	}
	if( m_tInfo.m_fX >m_max)
	{
		m_eDir=DIR_LEFT;
	}

	if( m_eDir == DIR_LEFT)
	{
		m_tInfo.m_fX -=2;
		m_tBodyBox.m_fX -=2;
	}

		if( m_eDir == DIR_RIGHT)
	{
		m_tInfo.m_fX +=2;
		m_tBodyBox.m_fX +=2;
	}
	

}

