#include "StdAfx.h"
#include "DirtPile.h"
#include "Treasure.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Effect.h"

CDirtPile::CDirtPile(void)
{
}

CDirtPile::CDirtPile(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:COtherObj(strName,fx,fy,fcx,fcy, Hp , Mp , Att)
{

}

CDirtPile::~CDirtPile(void)
{
}

void CDirtPile::Initialize(void)
{
	srand((unsigned)time(NULL));
	m_tFrame = FRAME(0,5,0,100);//프레임 초기화
	m_bDeadCheck=false;
	m_hit = false;
	m_DeadTime=10;
	m_Hp=50;
	m_dwFrameTime=GetTickCount();

	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, m_tInfo.m_fCY);
}
int	 CDirtPile::Progress(void)
{
	if(m_Hp <= 0)
		return 1;

	FrameCheck();
	if( m_hit ==true) //한대 맞으면 아이템을 생성하기 때문
	{
		OBJ_ITER iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
		
		for(int i = 0; i < 4 ; ++i)
		{
		
		int iValue;
		iValue = rand()%1;
		if( ((CPlayer*)(*iter))->GetDir() == DIR_RIGHT)
		m_pEffect = new CEffect("PICES",m_tInfo.m_fX + i*30,m_tInfo.m_fY - i*15,20,20);
		else
		m_pEffect = new CEffect("PICES",m_tInfo.m_fX - i*30,m_tInfo.m_fY - i*15,20,20);

		m_pEffect->SetType(EFFECT_DIRTPILE_POORF);
		m_pEffect->SetDeadTime(500);
		m_pEffect->SetFrame(0,1,0,100);
		m_pEffect->SetiType(iValue);
		m_pEffect->SetDir(((CPlayer*)(*iter))->GetDir());
		m_pEffect->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pEffect,OBJ_EFFECT);
		}

		CreateTreasure();
		m_hit = false; 
	}
	return 0;
}
void CDirtPile::Render(HDC _hdc)
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
void CDirtPile::Release(void)
{
}

void CDirtPile::FrameCheck(void)
{
	
	switch(m_Hp)
	{
	case 50:
	FrameMove(STATE_STAND,0,5,0,200);

	break;
	case 40:
			FrameMove(STATE_STAND,0,5,1,300);
		break;
	case 30:
			FrameMove(STATE_STAND,0,5,2,300);
		break;
	case 20:
			FrameMove(STATE_STAND,0,5,3,300);
		break;
	case 10:
			FrameMove(STATE_STAND,0,5,4,300);
		break;
	case 0:
		
		break;
	}
}
void CDirtPile::CreateTreasure(void)
{
	srand((unsigned)time(NULL));
	int iValue;


	iValue = rand()%4; //아이템이 랜덤
	
	OBJ_ITER iter1 = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
	

	if(m_Hp !=10)
	{
		switch(iValue)
		{
		case 0:
			m_pTreasure =  new CTreasure("GEM_GRAY", m_tInfo.m_fX, m_tInfo.m_fY-10, 18, 18);
			m_pTreasure->SetType(TREASURES_GRAY);
			m_pTreasure->SetDir(((CPlayer*)(*iter1))->GetDir());
			m_pTreasure->Initialize();

			
			CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);

			break;
		case 1:
		m_pTreasure =  new CTreasure("GEM_BLUE", m_tInfo.m_fX, m_tInfo.m_fY-10, 20, 20);
			m_pTreasure->SetType(TREASURES_BLUE);
			m_pTreasure->SetDir(((CPlayer*)(*iter1))->GetDir());
			m_pTreasure->Initialize();
			CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
			break;
		case 2:
		m_pTreasure =  new CTreasure("GEM_GREEN", m_tInfo.m_fX, m_tInfo.m_fY-10, 27, 35);
			m_pTreasure->SetType(TREASURES_GREEN);
			m_pTreasure->SetDir(((CPlayer*)(*iter1))->GetDir());
			m_pTreasure->Initialize();
			CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
			break;
		case 3:
		m_pTreasure =  new CTreasure("GEM_YELLOW", m_tInfo.m_fX, m_tInfo.m_fY-10, 36, 25);;
			m_pTreasure->SetType(TREASURES_YELLOW);
			m_pTreasure->SetDir(((CPlayer*)(*iter1))->GetDir());
			m_pTreasure->Initialize();
			CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
			break;

		}
	}
	
}