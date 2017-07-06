#include "StdAfx.h"
#include "BubbleDragon.h"
#include "ObjMgr.h"
#include "Bubble.h"
#include "Treasure.h"
#include "Potion.h"
#include "SoundMgr.h"

CBubbleDragon::CBubbleDragon(void)
{
}
CBubbleDragon::CBubbleDragon(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

CBubbleDragon::~CBubbleDragon(void)
{
}


void CBubbleDragon::Initialize(void)
{
	m_tFrame = FRAME(0,11,0,100);//프레임 초기화
	m_Dealay=30;
	m_fTime=30.0;
	m_fSpeed=3;
	m_bJump=false;
	m_bShow=false;

	m_dwFrameTime=GetTickCount();

	m_eDir=DIR_END;
	m_dwState=STATE_STAND;

	//충돌 박스 초기화
	m_tBodyBox=INFO(m_tInfo.m_fX-100,m_tInfo.m_fY+60,100,100);
	m_tAttackBox = INFO(m_tInfo.m_fX+100,m_tInfo.m_fY,300,200);
}

int CBubbleDragon::Progress(void)
{

	//if(m_Hp <= 0)
	//{
	//	DeadCheck();
	//	m_iDeadTime +=1;
	//	if(m_iDeadTime >=80) //죽은게 확인되어서 객체를 삭제한다.
	//	{
	//		return 1;
	//	}
	//	else if(m_iDeadTime >= 50)
	//	{
	//		if(m_strName != "POOFS")
	//		{
	//			m_tFrame = FRAME(0,4,0,100);
	//			m_strName ="POOFS";
	//			m_tInfo.m_fCX=48;
	//			m_tInfo.m_fCY=48;
	//			m_dwState=KEY_UP;
	//		}
	//	}
	//		
	//}
	//if(CCollisionMgr::GetInstance()->CollisionRectTile1(this) == 3) //플레이어와 타일과 충돌
	//{
	//	/*if( m_dwState == KEY_RIGHT)
	//	{
	//		m_dwState = KEY_LEFT;
	//		m_tFrame = FRAME(0,3,1,100);
	//	}

	//	if( m_dwState == KEY_LEFT )
	//	{
	//		m_dwState = KEY_RIGHT;
	//		m_tFrame = FRAME(0,3,0,100);
	//	}*/
	//}
	if(m_Hp <= 0)
	{
		CreateTreasure();
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_dragon_die.mp3");
		return 1; //죽은게 확인되어서 객체를 삭제한다.
	}
	MovePattern(); //좌표에 따라 어느쪽으로 갈지를 정해준다.
	KeyCheck(); //상태에 따라 움직임이 달라진다.
	FrameCheck(); //움직임 스프라이트
	CObj::Progress();
	

	return 0;
}

void CBubbleDragon::Render(HDC _hdc)
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

void CBubbleDragon::Release(void)
{
}
void CBubbleDragon::MovePattern(void)
{
	OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	OBJ_ITER iter_end = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].end();

	float disX = abs((*iter)->GetBodyBox()->m_fX - m_tAttackBox.m_fX) ;
	
	
	//플레이어와 일정거리가 성립이 되어야 움직인다.
	if( disX < 600 && disX > 500 ) 
	{
		/*if( (*iter)->GetBodyBox()->m_fX <  m_tBodyBox.m_fX)
		{
			if( m_dwState !=STATE_STAND)
			{
				m_dwState=STATE_STAND;
				m_tFrame = FRAME(11,0,0,100);
			}
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tBodyBox.m_fX + m_tBodyBox.m_fCX /2 )
		{
			if( m_dwState !=STATE_STAND)
			{
				m_dwState=STATE_STAND;
				m_tFrame = FRAME(11,0,0,100);
			}
		}*/
		
		if( (*iter)->GetBodyBox()->m_fX <  m_tAttackBox.m_fX) //플레이어가 왼쪽에 있는 경우
		{
			m_dwState = STATE_WALK;
			
			if(m_eDir != DIR_LEFT)
			{
				m_eDir=DIR_LEFT;
				m_tFrame = FRAME(11,6,1,200);
			}
		}
		else if( (*iter)->GetBodyBox()->m_fX >  m_tAttackBox.m_fX ) //플레이어가 오른쪽에 있는경우
		{
			
			if(m_eDir != DIR_RIGHT)
			{
			m_eDir=DIR_RIGHT;
			m_tFrame = FRAME(6,11,1,200);
			}
		}
		
	}
	else if( disX < 500 )  //일정거리가 좁혀질때까지 다가온다.
	{
		

		if( (*iter)->GetBodyBox()->m_fX <  m_tAttackBox.m_fX) //플레이어가 왼쪽
		{
			m_dwState = STATE_ATTACK;
			
					if( m_fTime <0)
			{
				m_fTime =30.0f;
				m_tFrame.m_iFrameStart=8;
			}
			if(m_eDir != DIR_LEFT)
			{
				m_eDir=DIR_LEFT;
				m_tFrame = FRAME(11,7,2,200);
			}
		}
		else
		{
			m_eDir = DIR_END;
		}
		
		
	}
	else
	{
		m_eDir = DIR_END;
	}

}
void CBubbleDragon::KeyCheck(void)
{
if( m_eDir == DIR_LEFT && m_dwState != STATE_ATTACK)
	{
		m_tInfo.m_fX -= m_fSpeed;
		m_tBodyBox.m_fX -= m_fSpeed;
		m_tAttackBox.m_fX -= m_fSpeed;
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_dragon_scoot.mp3");
	}

	if( m_eDir == DIR_RIGHT && m_dwState != STATE_ATTACK )
	{
		m_tInfo.m_fX += m_fSpeed;
		m_tBodyBox.m_fX += m_fSpeed;
		m_tAttackBox.m_fX += m_fSpeed;
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_dragon_scoot.mp3");
	}
	
}
void CBubbleDragon::FrameCheck(void)
{
	switch(m_dwState)
	{
	case STATE_WALK:

		if(m_eDir == DIR_RIGHT)
			FrameMove(STATE_WALK,6,11,1,100);
		else 
			FrameMoveReverse(STATE_WALK,11,6,1,100);
		break;
	case STATE_STAND:
		if(m_eDir == DIR_RIGHT)
			FrameMoveReverse(STATE_STAND,11,0,0,150);
		else 
			FrameMoveReverse(STATE_STAND,11,0,0,150);
		break;
	case STATE_ATTACK:
		if(m_eDir == DIR_RIGHT)
		{
			if(  m_tFrame.m_iFrameStart == 9)
			{
				if( m_fTime > 0)
				{

					FrameMoveReverse(STATE_ATTACK,9,9,2,200);
				}
				m_fTime -=1;
			}
			else
			{
			FrameMoveReverse(STATE_ATTACK,11,7,2,200);
			}
		}
		else 
			if(  m_tFrame.m_iFrameStart == 9)
			{
				if( m_fTime > 0)
				{
					if((int)m_fTime % 10 ==0)
					{
						CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_dragon_shoot.mp3");
					m_pBubble = new CBubble("BUBBLE",m_tBodyBox.m_fX- m_fTime, m_tBodyBox.m_fY,100,100,10);
					m_pBubble ->Initialize();
					((CBubble*)m_pBubble)->SetType(1);
					CObjMgr::GetInstance()->AddObject(m_pBubble,OBJ_MONSTER);
					}
					FrameMoveReverse(STATE_ATTACK,9,9,2,200);
				}
				m_fTime -=1;
				
			}
			else
			{
			FrameMoveReverse(STATE_ATTACK,11,7,2,200);
			}
		break;
	}
}
void CBubbleDragon::DeadCheck(void)
{
	if(m_bDeadCheck == false)
	{
		m_bDeadCheck =true;
		m_tFrame = FRAME(0,1,2,100);
		m_dwState=KEY_DOWN;
	}
}
void CBubbleDragon::CreateTreasure(void)
{
	srand((unsigned)time(NULL));
	int iValue;
	
	
	for( int i=0; i < 10 ; i++)
	{
		iValue = rand()%11;
	switch(iValue)
	{
	case 0:
		m_pTreasure =  new CTreasure("GEM_GRAY", m_tInfo.m_fX + i*5, m_tInfo.m_fY-20, 18, 18);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_GRAY);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);

		break;
	case 1:
	m_pTreasure =  new CTreasure("GEM_BLUE", m_tInfo.m_fX+ i*5, m_tInfo.m_fY-20, 20, 20);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_BLUE);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 2:
	m_pTreasure =  new CTreasure("GEM_GREEN", m_tInfo.m_fX+ i*5, m_tInfo.m_fY-20, 27, 35);
		((CTreasure*)m_pTreasure)->SetType(TREASURES_GREEN);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 3:
	m_pTreasure =  new CTreasure("GEM_YELLOW", m_tInfo.m_fX+ i*5, m_tInfo.m_fY-20, 36, 25);;
		((CTreasure*)m_pTreasure)->SetType(TREASURES_YELLOW);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 4:
		m_pTreasure = new CTreasure("GEM_RED",  m_tInfo.m_fX+ i*5, m_tInfo.m_fY-20, 52, 40);
	((CTreasure*)m_pTreasure)->SetType(TREASURES_RED);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 5:
	m_pTreasure = new CTreasure("GEM_VIOLET",  m_tInfo.m_fX+ i*5, m_tInfo.m_fY-20, 66, 50);
	((CTreasure*)m_pTreasure)->SetType(TREASURES_VIOLET);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 6:

	m_pTreasure = new CPotion("POTION_APPLE",  m_tInfo.m_fX+ i*3, m_tInfo.m_fY-20, 22, 20);
	((CPotion*)m_pTreasure)->SetType(RECOVER_ITEM_APPLE);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 7:
	m_pTreasure = new CPotion("POTION_CARROT",  m_tInfo.m_fX+ i*3, m_tInfo.m_fY-20, 63, 20);
	((CPotion*)m_pTreasure)->SetType(RECOVER_ITEM_CARROT);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 8:
	m_pTreasure = new CPotion("POTION_CHICKEN",  m_tInfo.m_fX+ i*3, m_tInfo.m_fY-20, 90, 60);
	((CPotion*)m_pTreasure)->SetType(RECOVER_ITEM_CHICKEN);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 9:
	m_pTreasure = new CPotion("POTION_SMALL_MANA",  m_tInfo.m_fX+ i*3, m_tInfo.m_fY-20, 16, 20);
	((CPotion*)m_pTreasure)->SetType(RECOVER_ITEM_SMALL_MANA);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	case 10:
	m_pTreasure = new CPotion("POTION_TALL_MANA",  m_tInfo.m_fX+ i*6, m_tInfo.m_fY-20, 30, 30);
	((CPotion*)m_pTreasure)->SetType(RECOVER_ITEM_TALL_MANA);
	m_pTreasure->Initialize();
	CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
	break;
	}
	}
	
}