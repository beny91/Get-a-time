#include "StdAfx.h"
#include "Skeleton.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "Treasure.h"


CSkeleton::CSkeleton(void)
{
}
CSkeleton::CSkeleton(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

CSkeleton::~CSkeleton(void)
{
}

void CSkeleton::Initialize(void)
{
	m_tFrame = FRAME(0,1,0,100);//프레임 초기화
	m_fTime=0.0f;
	m_fSpeed=6;
	m_bJump=false;
	m_bShow=false;
	m_iDeadTime=10;
	m_dwFrameTime=GetTickCount();

	m_eDir=DIR_END;
	m_dwState=STATE_STAND;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,100);
}

int CSkeleton::Progress(void)
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
				m_dwState=STATE_DEAD;

				CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_baz_whip.mp3");
			}
		}
			
	}
	CCollisionMgr::GetInstance()->CollisionRectTile1(this);
	if( CCollisionMgr::GetInstance()->CollisionAttack2(this, OBJ_PLAYER) )
	{
		memset(&m_tAttackBox,0,sizeof(INFO));
	}
	MovePattern(); //좌표에 따라 어느쪽으로 갈지를 정해준다.
	KeyCheck(); //상태에 따라 움직임이 달라진다.
	FrameCheck(); //움직임 스프라이트
	CObj::Progress();


	return 0;
}

void CSkeleton::Render(HDC _hdc)
{

	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2+ m_ptScroll.x ),
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2+ m_ptScroll.y),
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

void CSkeleton::Release(void)
{
}
void CSkeleton::MovePattern(void)
{
	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].end();

	float disX = abs((*iter)->GetBodyBox()->m_fX - m_tBodyBox.m_fX) ;

	//플레이어와 일정거리가 성립이 되어야 움직인다.
	if( disX > 300 ) 
	{
		if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX)
		{
			m_dwState=STATE_STAND;
			m_tFrame = FRAME(0,0,0,100);
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX + m_tBodyBox.m_fCX /2 )
		{
			m_dwState=STATE_STAND;
			m_tFrame = FRAME(3,3,3,100);
		}
	}
	else if( disX > 100 )  //일정거리가 좁혀질때까지 다가온다.
	{
		if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽에 있는 경우
		{
			m_dwState = STATE_WALK;
			if(m_eDir != DIR_LEFT)
			{
				m_eDir=DIR_LEFT;
				m_tFrame = FRAME(3,0,4,200);
			}
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX + m_tBodyBox.m_fCX /2) //플레이어가 오른쪽에 있는경우
		{
			m_dwState = STATE_WALK;
			if(m_eDir != DIR_RIGHT)
			{
			m_eDir=DIR_RIGHT;
			m_tFrame = FRAME(0,3,1,200);
			}
		}
		
	}
	else //공격 할때
	{
			if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX) //플레이어가 왼쪽
		{
			m_dwState = STATE_ATTACK;
			if(m_eDir != DIR_LEFT)
			{
				m_eDir=DIR_LEFT;
				m_tFrame = FRAME(3,0,4,200);
			}
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX + m_tBodyBox.m_fCX /2 ) //플레이어가 오른쪽
		{
			m_dwState = STATE_ATTACK;
			if(m_eDir != DIR_RIGHT)
			{
			m_eDir=DIR_RIGHT;
			m_tFrame = FRAME(0,3,2,200);
			}
		}
	}
	if( m_tFrame.m_iFrameStart ==3 && m_dwState == STATE_ATTACK)
	{
		CreateAttackBox();
	}
	else
	{
		memset(&m_tAttackBox,0,sizeof(INFO));
	}


}
void CSkeleton::KeyCheck(void)
{

	if(m_bDeadCheck ==true)	
			return;

	if( m_eDir == DIR_LEFT && m_dwState != STATE_ATTACK)
	{
		m_tInfo.m_fX -= m_fSpeed;
		m_tBodyBox.m_fX -= m_fSpeed;

	}

	if( m_eDir == DIR_RIGHT && m_dwState != STATE_ATTACK )
	{
		m_tInfo.m_fX += m_fSpeed;
		m_tBodyBox.m_fX += m_fSpeed;
	}

	m_tInfo.m_fY += m_fSpeed;
	m_tBodyBox.m_fY += m_fSpeed;


}
void CSkeleton::FrameCheck(void)
{
	

	switch(m_dwState)
	{
	case STATE_WALK:

		if(m_eDir == DIR_RIGHT)
			FrameMove(STATE_WALK,0,3,1,100);
		else 
			FrameMoveReverse(STATE_WALK,3,0,4,100);
		break;
	case STATE_STAND:
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
		break;
	case STATE_DEAD:
			FrameMove(STATE_DEAD,0,4,0,200);
		break;

	}
	
}
void CSkeleton::CreateAttackBox(void)
{
	if( m_dwState==STATE_ATTACK  &&   m_eDir == DIR_LEFT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX -70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f  ;
		m_tAttackBox.m_fCX = 25;
		m_tAttackBox.m_fCY = 25;
	}
	else if( m_dwState==STATE_ATTACK  && m_eDir == DIR_RIGHT)
	{
		m_tAttackBox.m_fX = m_tInfo.m_fX +70;
		m_tAttackBox.m_fY = m_tInfo.m_fY +17.5f ;
		m_tAttackBox.m_fCX = 30;
		m_tAttackBox.m_fCY = 30;
	}
	else if( m_dwState==STATE_ATTACK_DOWN  && (m_eDir == DIR_DOWN || m_eDir == DIR_RIGHT || m_eDir == DIR_LEFT))
	{
		m_tAttackBox.m_fX = m_tBodyBox.m_fX  ;
		m_tAttackBox.m_fY = m_tBodyBox.m_fY + m_tBodyBox.m_fCY-30   ;
		m_tAttackBox.m_fCX = 30;
		m_tAttackBox.m_fCY = 30;
	}
}
void CSkeleton::DeadCheck(void)
{
	if(m_bDeadCheck == false)
	{
		m_bDeadCheck =true;
	}
}
void CSkeleton::CreateTreasure(void)
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