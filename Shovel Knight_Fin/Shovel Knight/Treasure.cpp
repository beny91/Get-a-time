#include "StdAfx.h"
#include "Treasure.h"
#include "COllisionMgr.h"

CTreasure::CTreasure(void)
{
}
CTreasure::CTreasure(string strName, float fx, float fy, float fcx, float fcy,int _price , int Hp, int Mp, int Att )
:CItem(strName, fx, fy, fcx, fcy,_price, Hp, Mp, Att)
{

}

CTreasure::~CTreasure(void)
{
}

void CTreasure::Initialize(void)
{
	m_tFrame = FRAME(0,0,0,100);//������ �ʱ�ȭ
	m_bDeadCheck=false;
	m_bSparkle=false;
	m_bJump = true;

	m_fTime = 0; //������ ����� �ð�.
	m_DeadTime=300;
	m_dwFrameTime=GetTickCount();

	CreateTreasure();
	
	
	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, 50);
}
int	 CTreasure::Progress(void)
{
	if( CCollisionMgr::GetInstance()->CollisionRectTile2(this)== 1 )
	{
		m_bJump =false;
		m_fTime = 0;
	}

	if(m_bDeadCheck == true && !m_bSparkle ) //�������� ������� ���� ��Ŭ�� ����
	{
		if( m_DeadTime > 0) //�ڿ������� ������� ���� ��ƼŬ�� ����.
		{
			m_bSparkle=true;
		m_strName="PICKUP_SPARKLE";
		m_tFrame = FRAME(0,2,0,100);
		
		m_DeadTime=30;
		m_tInfo.m_fCX=21;
		m_tInfo.m_fCY=21;
		}
			
		
	}

		if( m_DeadTime <25 && m_bDeadCheck ==true ) //��ƼŬ�� ������� ���ư��� �������.
		 return 1;
		
		if(m_bSparkle ==true)
		FrameMove(STATE_STAND,0,2,0,100);
		
		if(m_DeadTime <=50 && m_bDeadCheck !=true)// �������� �����ǰ� �ð��� ������ �����Ÿ���.
		FrameMove(STATE_STAND,0,1,0,200);

	if( m_DeadTime <0) //�ð��� �� �Ǹ� ���� üũ�� �Ѵ�.
		m_bDeadCheck=true;
	
	m_DeadTime--;
	
	if(m_bJump ==true)
	{
		MoveCheck();
		Jump();
		
	}

	return 0;
}
void CTreasure::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
		static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//��µǴ� �̹����� ���� X��.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//�̹��� ��� ���� ����.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//���� ���� ��.s
}
void CTreasure::Release(void)
{

}

void CTreasure::CreateTreasure(void)
{
	switch(m_eType)
	{
	case TREASURES_GRAY:
		m_iPrice=1;
		break;
	case TREASURES_BLUE:
		m_iPrice=5;
		break;
	case TREASURES_GREEN:
		m_iPrice=10;
		break;
	case TREASURES_YELLOW:
		m_iPrice=20;
		break;
	case TREASURES_RED:
		m_iPrice=50;
		break;
	case TREASURES_VIOLET:
		m_iPrice=200;
		break;

	}
}
void CTreasure::MoveCheck(void)
{
	srand((unsigned)time(NULL));
	int iValue=rand()%10 +1;
	switch(m_eDir)
	{
	case DIR_UP :
		
		break;
	case DIR_LEFT :
		m_tInfo.m_fX -=iValue;
		m_tBodyBox.m_fX -=iValue;
		break;
	case DIR_RIGHT :
		m_tInfo.m_fX +=iValue;
		m_tBodyBox.m_fX +=iValue;
		break;
	}
}
void CTreasure::Jump(void)
{
	if(m_bJump == false )
		return;

	
	m_fTime += 0.8f;		//GetTickCount....

	if(/*(15-m_Gravity)<0*/ (15 * -1 + (0.98 * m_fTime * m_fTime) / 2 )>0) //���� ���¿��� �ִ����� ��� �������� ���������� ���°�
	{
			m_bJump =true;
		
	}
	m_tInfo.m_fY += static_cast<float>(15 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	m_tBodyBox.m_fY += static_cast<float>( 15* -1 + (0.98 * m_fTime * m_fTime) / 2);
	

}