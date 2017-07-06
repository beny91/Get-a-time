#include "StdAfx.h"
#include "Beeto.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Treasure.h"
#include "SoundMgr.h"

CBeeto::CBeeto(void)
{
}
CBeeto::CBeeto(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

CBeeto::~CBeeto(void)
{
}


void CBeeto::Initialize(void)
{
	m_tFrame = FRAME(0,3,1,100);//프레임 초기화
	m_fTime=0.0f;
	m_fSpeed=1;
	m_min=m_tInfo.m_fX -200;
	m_max=m_tInfo.m_fX +150;

	m_bJump=false;
	m_bShow=false;
	m_bDeadCheck=false;
	m_iDeadTime=10;

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_LEFT;
	m_dwState=KEY_LEFT;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,50);
}

int CBeeto::Progress(void)
{

	if(m_Hp <= 0)
	{
		DeadCheck();
		m_iDeadTime +=1;
		if(m_iDeadTime >=80) //죽은게 확인되어서 객체를 삭제한다.
		{
			CreateTreasure();
			return 1;
		}
		else if(m_iDeadTime >= 50)
		{
			if(m_strName != "POOFS")
			{
				m_tFrame = FRAME(0,4,0,100);
				m_strName ="POOFS";
				m_tInfo.m_fCX=48;
				m_tInfo.m_fCY=48;
				m_dwState=KEY_UP;
				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_baz_whip.mp3");
			}
		}
			
	}
	if(CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 3) //플레이어와 타일과 충돌
	{
		/*if( m_dwState == KEY_RIGHT)
		{
			m_dwState = KEY_LEFT;
			m_tFrame = FRAME(0,3,1,100);
		}

		if( m_dwState == KEY_LEFT )
		{
			m_dwState = KEY_RIGHT;
			m_tFrame = FRAME(0,3,0,100);
		}*/
	}
	MovePattern(); //좌표에 따라 어느쪽으로 갈지를 정해준다.
	KeyCheck(); //상태에 따라 움직임이 달라진다.
	FrameCheck(); //움직임 스프라이트
	CObj::Progress();
	

	return 0;
}

void CBeeto::Render(HDC _hdc)
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

void CBeeto::Release(void)
{
}
void CBeeto::MovePattern(void)
{
	if(m_bDeadCheck ==true)	
			return;
	if( m_tBodyBox.m_fX > m_max)
	{
		if( m_dwState != KEY_LEFT)
		{
			m_dwState = KEY_LEFT;
			m_tFrame = FRAME(0,3,1,100);
		}
	}
	else if( m_tBodyBox.m_fX <m_min)
	{
		if( m_dwState != KEY_RIGHT )
		{
			m_dwState = KEY_RIGHT;
			m_tFrame = FRAME(0,3,0,100);
		}
	}
}
void CBeeto::KeyCheck(void)
{

	if( m_dwState & KEY_LEFT)
	{
		m_tInfo.m_fX -= m_fSpeed;
		m_tBodyBox.m_fX -= m_fSpeed;
		
	}

	if( m_dwState & KEY_RIGHT)
	{
		m_tInfo.m_fX += m_fSpeed;
		m_tBodyBox.m_fX += m_fSpeed;		
	}

	m_tInfo.m_fY += m_fSpeed;
	m_tBodyBox.m_fY += m_fSpeed;
}
void CBeeto::FrameCheck(void)
{
	switch(m_dwState)
	{
	case KEY_RIGHT:
		FrameMove(STATE_WALK,0,3,0,300);
	break;
	case KEY_LEFT:
		FrameMove(STATE_WALK,0,3,1,300);
	break;
	case KEY_DOWN:
		FrameMove(STATE_WALK,0,1,2,100);
	break;
	case KEY_UP:
		FrameMove(STATE_WALK,0,4,0,200);
	break;
	}
}
void CBeeto::DeadCheck(void)
{
	if(m_bDeadCheck == false)
	{
		m_bDeadCheck =true;
		m_tFrame = FRAME(0,1,2,100);
		m_dwState=KEY_DOWN;
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_beetle_flip.mp3");
	}
}

void CBeeto::CreateTreasure(void)
{
	srand((unsigned)time(NULL));
	int iValue;
	iValue = rand()%4;
	
	switch(iValue)
	{
	case 0:
		m_pTreasure =  new CTreasure("GEM_GRAY", m_tInfo.m_fX, m_tInfo.m_fY-20, 18, 18);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_GRAY);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);

		break;
	case 1:
	m_pTreasure =  new CTreasure("GEM_BLUE", m_tInfo.m_fX, m_tInfo.m_fY-20, 20, 20);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_BLUE);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 2:
	m_pTreasure =  new CTreasure("GEM_GREEN", m_tInfo.m_fX, m_tInfo.m_fY-20, 27, 35);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_GREEN);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 3:
	m_pTreasure =  new CTreasure("GEM_YELLOW", m_tInfo.m_fX, m_tInfo.m_fY-20, 36, 25);;
		((CTreasure*)m_pTreasure)->SetType(TREASURES_YELLOW);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;

	}
	
}