#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
}


CEffect::CEffect(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:CObj(strName,fx,fy,fcx,fcy, Hp, Mp, Att)
{

}

void CEffect::Initialize(void)
{
	srand((unsigned)time(NULL));
	m_bDeadCheck=false;
	m_bJump = true;
	m_fTime = 0;
	m_dwFrameTime=GetTickCount();

	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, m_tInfo.m_fCY);
		
}
int	 CEffect::Progress(void)
{
	if( m_DeadTime <0)
		return 1;

	if( m_eType == EFFECT_DIRTPILE_POORF)
	{
		Jump();
		MoveCheck();
	}
	FrameCheck();
	m_DeadTime--;
	return 0;
}
void CEffect::Render(HDC _hdc)
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
void CEffect::Release(void)
{
}
void CEffect::MoveCheck(void)
{
	
	int iValue;
	iValue=rand()%10+1;

	switch(m_eDir)
	{
	case DIR_UP:
		
		break;
	case DIR_LEFT:
		m_tInfo.m_fX -=iValue;
		m_tBodyBox.m_fX -=iValue;
		break;
	case DIR_RIGHT:
			m_tInfo.m_fX +=iValue;
		m_tBodyBox.m_fX +=iValue;
		break;
	}
}
void CEffect::FrameCheck(void)
{
	switch(m_eType)
	{
	case EFFECT_DIRT_POORF:
		FrameMove(STATE_STAND,0,6,0,100);
		break;
	case EFFECT_DIRTPILE_POORF:
		FrameMove(STATE_STAND,m_itype,m_itype,0,100);
		break;
	case EFFECT_ATTTECK_DOWN:
		FrameMove(STATE_STAND,0,3,0,100);
		break;
	}
}
void CEffect::Jump(void)
{
	if(m_bJump == false )
		return;

	
	m_fTime += 0.8f;		//GetTickCount....

	if(/*(15-m_Gravity)<0*/ (20 * -1 + (0.98 * m_fTime * m_fTime) / 2 )>0) //점프 상태에서 최대점을 찍고 내려오는 시점에서의 상태값
	{
			m_bJump =true;
		
	}
	m_tInfo.m_fY += static_cast<float>(20 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	m_tBodyBox.m_fY += static_cast<float>( 20* -1 + (0.98 * m_fTime * m_fTime) / 2);
}