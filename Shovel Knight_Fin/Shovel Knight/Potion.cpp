#include "StdAfx.h"
#include "Potion.h"
#include "COllisionMgr.h"
#include "Potion.h"

CPotion::CPotion(void)
{
}

CPotion::~CPotion(void)
{
}

CPotion::CPotion(string strName, float fx, float fy, float fcx, float fcy,int _price , int Hp, int Mp, int Att )
:CItem(strName, fx, fy, fcx, fcy,_price, Hp, Mp, Att)
{

}


void CPotion::Initialize(void)
{
	m_tFrame = FRAME(0,0,0,100);//������ �ʱ�ȭ
	m_bDeadCheck=false;
	m_bSparkle=false;
	m_DeadTime=300;
	m_bJump=true;
	m_fTime = 0; //������ ����� �ð�.
	m_dwFrameTime=GetTickCount();
	CreateTreasure();
	
	
	m_tBodyBox = INFO(m_tInfo.m_fX, m_tInfo.m_fY, m_tInfo.m_fCX, 45);
}
int	 CPotion::Progress(void)
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
		Jump();
		
	}
	

	return 0;
}
void CPotion::Render(HDC _hdc)
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
void CPotion::Release(void)
{

}

void CPotion::CreateTreasure(void)
{
	switch(m_eType)
	{
	case RECOVER_ITEM_CARROT:
		m_Hp=20;
		break;
	case RECOVER_ITEM_APPLE:
		m_Hp=20;
		break;
	case RECOVER_ITEM_CHICKEN:
		m_Hp=80;
		break;
	case RECOVER_ITEM_SMALL_MANA:
		m_Mp=5;
		break;
	case RECOVER_ITEM_TALL_MANA:
		m_Mp=30;
		break;
	case RECOVER_ITEM_HP_MEAL:
		m_HpMax=20;
		break;
	case RECOVER_ITEM_MP_MEAL:
		m_MpMax=20;
		break;
	}

}
void CPotion::Jump(void)
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