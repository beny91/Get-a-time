#include "StdAfx.h"
#include "Bubble.h"

CBubble::CBubble(void)
{
}

CBubble::~CBubble(void)
{
}
CBubble::CBubble(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

void CBubble::Initialize(void)
{
	m_tFrame = FRAME(0,3,0,100);//프레임 초기화
	m_fTime=0.0f;
	m_fSpeed=7;
	m_min = m_tInfo.m_fX -200;
	m_max = m_tInfo.m_fY -400;
	m_bJump=false;
	m_bShow=false;
	m_bDeadCheck=false;
	m_iType=0;

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_RIGHT;
	m_dwState=STATE_STAND;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,100,100);
}

int CBubble::Progress(void)
{
	
	if(m_Hp <= 0)
	{
		if( m_bDeadCheck == false)
		{
			m_tFrame = FRAME(0,1,1,100);
			m_bDeadCheck =true ;//죽은게 확인되어서 객체를 삭제한다.
		}
	}
	if(m_tInfo.m_fY <m_max)
	{
		if( m_bDeadCheck == false)
		{
			m_tFrame = FRAME(0,1,1,100);
			m_bDeadCheck =true ;//죽은게 확인되어서 객체를 삭제한다.
		}
	}
	MovePattern();
	FrameCheck();
	if( m_bDeadCheck == true)
	{
		if(m_tFrame.m_iFrameStart ==1)
			return 1;
	}
	CObj::Progress();


	return 0;
}

void CBubble::Render(HDC _hdc)
{
	
	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
			static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		((*m_mapBmp)[m_strName])->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//빼고 싶은 색.s
	
	if( m_bShow == true ) //충돌 박스를 보여주는 경우
	{
		//바디 박스
		HPEN MyBrush1, OldBrush1;
		MyBrush1 = (HPEN)CreatePen(4,5,(RGB(0,100,255)));
		OldBrush1 = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush1);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), 
			static_cast<int>( m_tBodyBox.m_fX - m_tBodyBox.m_fCX/2 )+ m_ptScroll.x, 
			static_cast<int>( m_tBodyBox.m_fY - m_tBodyBox.m_fCY/2)+ m_ptScroll.y,
			static_cast<int>(m_tBodyBox.m_fX + m_tBodyBox.m_fCX/2)+ m_ptScroll.x,
			static_cast<int>(m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2)+ m_ptScroll.y);
		SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
		DeleteObject(MyBrush1);

		// 무기 박스

		MyBrush1 = (HPEN)CreatePen(4,5,(RGB(255,255,255)));
		OldBrush1 = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush1);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), m_AttackRect.left, m_AttackRect.top, m_AttackRect.right, m_AttackRect.bottom);
		SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
		DeleteObject(MyBrush1);
	}
}

void CBubble::Release(void)
{
}
void CBubble::FrameCheck(void)
{
	if( m_bDeadCheck == true)
	{
		FrameMove(STATE_WALK,0,1,1,200);
	}
	else
	{
		FrameMove(STATE_WALK,0,3,0,200);
	}
}
void CBubble::MovePattern(void)
{
	if( m_iType ==0 )
	{
		m_tInfo.m_fY -=2;
		m_tBodyBox.m_fY -=2;
	}

	if( m_iType ==1)
	{
		if( m_tInfo.m_fX > m_min )
		{
			m_tInfo.m_fX -= m_fSpeed*2;
			m_tBodyBox.m_fX -= m_fSpeed*2;
		}
		else
		{
			m_tInfo.m_fY -=2;
			m_tBodyBox.m_fY -=2;
		}
	}
	
}