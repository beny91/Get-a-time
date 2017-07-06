#include "StdAfx.h"
#include "Divedrake.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CDivedrake::CDivedrake(void)
{
}

CDivedrake::~CDivedrake(void)
{
}

CDivedrake::CDivedrake(string strName, float fx, float fy, float fcx, float fcy  , int Hp , int Mp , int Att  )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

void CDivedrake::Initialize(void)
{
	m_angle= 0.00f;
	m_tFrame = FRAME(0,2,0,100);//프레임 초기화
	m_fTime=0.0f;
	m_fSpeed=4.0f;
	m_bJump=false;
	m_bShow=false;
	m_bDeadCheck=false;
	m_iDeadTime=10;

	m_dwFrameTime=GetTickCount();

	m_eDir=DIR_RIGHT;
	m_dwState=STATE_WALK;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,40);
}

int CDivedrake::Progress(void)
{
	if(m_Hp <= 0)
	{
		DeadCheck();
		m_iDeadTime +=1;
		if(m_iDeadTime >=40) //죽은게 확인되어서 객체를 삭제한다.
		{
			return 1;
		}
		else if(m_iDeadTime >= 20)
		{
			
			if(m_strName != "POOFS")
			{
				m_tFrame = FRAME(0,4,0,100);
				m_strName ="POOFS";
				m_tInfo.m_fCX=48;
				m_tInfo.m_fCY=48;
				m_dwState=KEY_DOWN;
				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_baz_whip.mp3");
			}
		}
			
	}
	MovePattern(); //좌표에 따라 어느쪽으로 갈지를 정해준다.

	FrameCheck(); //움직임 스프라이트
	CObj::Progress();


	return 0;
}

void CDivedrake::Render(HDC _hdc)
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
		MyBrush1 = (HPEN)CreatePen(4,5,(RGB(0,0,0)));
		OldBrush1 = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush1);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), 
				static_cast<int>( m_tBodyBox.m_fX - m_tBodyBox.m_fCX/2 ) + m_ptScroll.x, 
		 static_cast<int>( m_tBodyBox.m_fY - m_tBodyBox.m_fCY/2) + m_ptScroll.y,
		 static_cast<int>(m_tBodyBox.m_fX + m_tBodyBox.m_fCX/2) + m_ptScroll.x,
		 static_cast<int>(m_tBodyBox.m_fY + m_tBodyBox.m_fCY/2) + m_ptScroll.y);
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

void CDivedrake::Release(void)
{
}
void CDivedrake::MovePattern(void)
{
	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].end();

	float disX = abs((*iter)->GetBodyBox()->m_fX - m_tBodyBox.m_fX) ;

	switch( m_iPattern )
	{
	case DRAKE_TURNAROUND:
		
		m_tInfo.m_fX += cos( m_angle / (180/PI))*m_fSpeed;
		m_tInfo.m_fY += -sin( m_angle / (180/PI));
		m_tBodyBox.m_fX +=cos( m_angle / (180/PI))*m_fSpeed;
		m_tBodyBox.m_fY += -sin( m_angle / (180/PI));
		m_angle += 1.8f;
	
		if( -sin( m_angle / (180/PI)) == 1)
		{
			
			if( m_eDir == DIR_LEFT)
				m_tFrame = FRAME(0,2,0,100);
			m_eDir = DIR_RIGHT;
		}
		else if( -sin( m_angle / (180/PI)) == -1)
		{
			
			if( m_eDir == DIR_RIGHT)
				m_tFrame = FRAME(2,0,1,100);
			m_eDir = DIR_LEFT;
		}

		break;
	case DRAKE_UPDOWN:

		
		m_tInfo.m_fY += -sin( m_angle / (180/PI)) * m_fSpeed;
		m_tBodyBox.m_fY += -sin( m_angle / (180/PI)) * m_fSpeed;
		m_angle += 1.8f;
		
		if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
		{
			if( m_eDir == DIR_RIGHT)
				m_tFrame = FRAME(0,2,0,100);
			m_eDir=DIR_LEFT;
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX) //플레이어가 오른쪽에
		{
			if( m_eDir == DIR_LEFT)
				m_tFrame = FRAME(2,0,1,100);
			m_eDir=DIR_RIGHT;
		}
		break;

	case DRAKE_SHORTTURNAROUND:
		
		m_tInfo.m_fX += cos( m_angle / (180/PI));
		m_tInfo.m_fY += -sin( m_angle / (180/PI));
		m_tBodyBox.m_fX +=cos( m_angle / (180/PI));
		m_tBodyBox.m_fY += -sin( m_angle / (180/PI));
		m_angle += 1.8f;

		if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
		{
			if( m_eDir == DIR_RIGHT)
				m_tFrame = FRAME(0,2,0,100);
			m_eDir=DIR_LEFT;
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX) //플레이어가 오른쪽에
		{
			if( m_eDir == DIR_LEFT)
				m_tFrame = FRAME(2,0,1,100);
			m_eDir=DIR_RIGHT;
		}
		break;
	}
	


}
void CDivedrake::KeyCheck(void)
{

	if(m_bDeadCheck ==true)	
			return;

	if( m_eDir == DIR_LEFT && m_dwState != STATE_ATTACK)
	{
		
	}

	if( m_eDir == DIR_RIGHT && m_dwState != STATE_ATTACK )
	{
		
	}

	


}
void CDivedrake::FrameCheck(void)
{
	switch(m_dwState)
	{
	case STATE_WALK:

		if(m_eDir == DIR_RIGHT)
			FrameMove(STATE_WALK,0,2,0,200);
		else 
			FrameMoveReverse(STATE_WALK,2,0,1,200);
		break;
	case KEY_DOWN:
		FrameMove(STATE_WALK,0,4,0,200);
	break;
	/*case STATE_STAND:
		if(m_eDir == DIR_RIGHT)
			FrameMove(STATE_STAND,0,0,0,100);
		else 
			FrameMoveReverse(STATE_STAND,3,3,3,100);
		break;
	case STATE_ATTACK:
		if(m_eDir == DIR_RIGHT)
			FrameMove(STATE_ATTACK,0,3,2,150);
		else 
			FrameMoveReverse(STATE_ATTACK,3,0,5,150);
		break;*/
	}
}
void CDivedrake::DeadCheck(void)
{
	if(m_bDeadCheck == false)
	{
		m_bDeadCheck =true;
		m_tFrame = FRAME(0,1,2,100);
		m_dwState=KEY_DOWN;
	}
}