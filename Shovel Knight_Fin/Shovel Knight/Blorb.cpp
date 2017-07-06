#include "StdAfx.h"
#include "Blorb.h"

CBlorb::CBlorb(void)
{
}
CBlorb::CBlorb(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att )
:CMonster(strName, fx, fy, fcx, fcy ,Hp,Mp,Att)
{

}

CBlorb::~CBlorb(void)
{
}


void CBlorb::Initialize(void)
{
	m_tFrame = FRAME(0,5,1,100);//������ �ʱ�ȭ
	m_fTime=0.0f;
	m_fSpeed=7;
	m_bJump=false;
	m_bShow=false;

	m_dwFrameTime=GetTickCount();
	m_eDir = DIR_RIGHT;
	m_dwState=STATE_STAND;

	//�浹 �ڽ� �ʱ�ȭ
	m_tBodyBox=INFO(m_tInfo.m_fX,m_tInfo.m_fY,50,25);
}

int CBlorb::Progress(void)
{
	if(m_Hp <= 0)
		return 1; //������ Ȯ�εǾ ��ü�� �����Ѵ�.



	CObj::Progress();


	return 0;
}

void CBlorb::Render(HDC _hdc)
{
	
	TransparentBlt(_hdc,
		static_cast<int>(m_tInfo.m_fX - m_tInfo.m_fCX / 2 )+ m_ptScroll.x,
			static_cast<int>(m_tInfo.m_fY - m_tInfo.m_fCY / 2)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		((*m_mapBmp)[m_strName])->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//��µǴ� �̹����� ���� X��.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//�̹��� ��� ���� ����.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 255, 0));		//���� ���� ��.s
	
	if( m_bShow == true ) //�浹 �ڽ��� �����ִ� ���
	{
		//�ٵ� �ڽ�
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

		// ���� �ڽ�

		MyBrush1 = (HPEN)CreatePen(4,5,(RGB(255,255,255)));
		OldBrush1 = (HPEN)SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), MyBrush1);
		Rectangle((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), m_AttackRect.left, m_AttackRect.top, m_AttackRect.right, m_AttackRect.bottom);
		SelectObject((*m_mapBmp)["BACK_BUFFER"]->GetMemDC(), GetStockObject(NULL_BRUSH));
		DeleteObject(MyBrush1);
	}
}

void CBlorb::Release(void)
{
}