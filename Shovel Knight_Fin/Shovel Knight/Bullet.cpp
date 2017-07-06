#include "StdAfx.h"
#include "Bullet.h"
#include "CollisionMgr.h"

CBullet::CBullet(void)
{
}

CBullet::CBullet(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:CObj(strName,fx,fy,fcx,fcy, Hp, Mp, Att)
{

}

CBullet::~CBullet(void)
{
}

void CBullet::Initialize(void)
{

	m_tFrame = FRAME(0,3,0,100);//프레임 초기화
	m_fTime=0.0f;
	m_fSpeed=7;
	
	m_bJump=false;
	m_bShow=false;

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_LEFT;
	m_dwState=STATE_STAND;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,m_tInfo.m_fCX,m_tInfo.m_fCY);
	m_tAttackBox = INFO(m_tInfo.m_fX,m_tInfo.m_fY,m_tInfo.m_fCX,m_tInfo.m_fCY);
}

int CBullet::Progress(void)
{

	if(CCollisionMgr::GetInstance()->CollisionAttack2(this,OBJ_PLAYER))
		return 1; //충돌하면 데미지 주고 삭제
	if(CCollisionMgr::GetInstance()->CollisionAttack(this,OBJ_MONSTER))
		return 1; //충돌하면 데미지 주고 삭제

	KeyCheck();
	FrameCheck();
	CObj::Progress();


	return 0;
}

void CBullet::Render(HDC _hdc)
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

	if( m_bShow == true ) //충돌 박스를 보여주는 경우
	{
		//바디 박스
		HPEN MyBrush1, OldBrush1;
		MyBrush1 = (HPEN)CreatePen(4,5,(RGB(0,0,0)));
		OldBrush1 = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush1);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), 
			static_cast<int>( m_tBodyBox.m_fX - m_tBodyBox.m_fCX/2 ), 
			static_cast<int>( m_tBodyBox.m_fY - m_tBodyBox.m_fCY/2),
			static_cast<int>(m_tBodyBox.m_fX + m_tBodyBox.m_fCX/2),
			static_cast<int>(m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2));
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

void CBullet::Release(void)
{
}

void CBullet::KeyCheck(void)
{
	
	if(m_eDir == DIR_RIGHT)
	{
		m_tInfo.m_fX +=m_fSpeed;
		m_tBodyBox.m_fX +=m_fSpeed;
		m_tAttackBox.m_fX +=m_fSpeed;
	}

	if(m_eDir == DIR_LEFT)
	{
		m_tInfo.m_fX -=m_fSpeed;
		m_tBodyBox.m_fX -=m_fSpeed;
		m_tAttackBox.m_fX -=m_fSpeed;
	}
}
void CBullet::FrameCheck(void)
{
	switch(m_eDir)
	{
	case DIR_RIGHT:
		FrameMove(STATE_STAND,0,3,0,100);
		break;
	case DIR_LEFT:
		FrameMoveReverse(STATE_STAND,3,0,1,100);
		break;
	}
}