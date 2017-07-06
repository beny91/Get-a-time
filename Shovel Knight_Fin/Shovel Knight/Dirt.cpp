#include "StdAfx.h"
#include "Dirt.h"
#include "Treasure.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "SoundMgr.h"

CDirt::CDirt(void)
{
}

CDirt::~CDirt(void)
{
}

CDirt::CDirt(string strName, float fx, float fy, float fcx, float fcy , int Hp, int Mp , int Att )
:COtherObj(strName,fx,fy,fcx,fcy, Hp , Mp , Att)
{

}

void CDirt::Initialize(void)
{
	m_tFrame = FRAME(0,0,0,100);//프레임 초기화
	m_bDeadCheck=false;
	m_DeadTime=10;
	m_dwFrameTime=GetTickCount();
	CreateDirt();
	
	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, m_tInfo.m_fCY);
}
int	 CDirt::Progress(void)
{
	if( m_DeadTime <0)
	{
		if( m_eType == DIRT_SMALL)
		m_pEffect = new CEffect("MPOOFS_S",m_tInfo.m_fX , m_tInfo.m_fY , m_tInfo.m_fCX,m_tInfo.m_fCY);
		else
		m_pEffect = new CEffect("MPOOFS_B",m_tInfo.m_fX , m_tInfo.m_fY , m_tInfo.m_fCX,m_tInfo.m_fCY);
		m_pEffect->SetType(EFFECT_DIRT_POORF);
		m_pEffect->SetDeadTime(10);
		m_pEffect->SetFrame(0,6,0,100);
		m_pEffect->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pEffect,OBJ_EFFECT);
		CSoundMgr::GetInstance()->PlayMonsterSound(L"sfx_dirtblock_money.mp3");
		CreateTreasure();
		return 1;
	}
	if( m_Hp <= 0)
	{
		if( m_bDeadCheck == false)
		{
			m_bDeadCheck=true;
			m_tFrame = FRAME(0,2,1,200);
		}
		m_DeadTime -=1;
	}
	FrameCheck();
	return 0;
}
void CDirt::Render(HDC _hdc)
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
void CDirt::Release(void)
{
}
void CDirt::CreateDirt(void)
{
	switch(m_eType)
	{
	case DIRT_SMALL:
		
		break;
	case DIRT_BIG:
		break;
	}
}

void CDirt::FrameCheck(void)
{
	if( m_bDeadCheck ==true)
	FrameMove(STATE_STAND,0,2,1,200);
	else
	FrameMove(STATE_STAND,0,0,0,100);
}
void CDirt::CreateTreasure(void)
{
	srand((unsigned)time(NULL));
	int iValue;
	switch(m_eType)
	{
	case DIRT_SMALL:
		iValue = rand()%2;
		break;
	case DIRT_BIG:
		iValue = rand()%4;
		break;
	}
	
	switch(iValue)
	{
	case 0:
		m_pTreasure =  new CTreasure("GEM_GRAY", m_tInfo.m_fX, m_tInfo.m_fY, 18, 18);
		m_pTreasure->SetType(TREASURES_GRAY);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);

		break;
	case 1:
	m_pTreasure =  new CTreasure("GEM_BLUE", m_tInfo.m_fX, m_tInfo.m_fY, 20, 20);
		m_pTreasure->SetType(TREASURES_BLUE);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 2:
	m_pTreasure =  new CTreasure("GEM_GREEN", m_tInfo.m_fX, m_tInfo.m_fY, 27, 35);
		m_pTreasure->SetType(TREASURES_GREEN);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;
	case 3:
	m_pTreasure =  new CTreasure("GEM_YELLOW", m_tInfo.m_fX, m_tInfo.m_fY, 36, 25);;
		m_pTreasure->SetType(TREASURES_YELLOW);
		m_pTreasure->Initialize();
		CObjMgr::GetInstance()->AddObject(m_pTreasure ,OBJ_ITEM);
		break;

	}
	
}