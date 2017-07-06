#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::CItem(string strName, float fx, float fy, float fcx, float fcy,int _price , int Hp , int Mp , int Att )
:CObj(strName, fx, fy, fcx, fcy, Hp, Mp, Att), m_iPrice(_price)
{

}

CItem::~CItem(void)
{
}


void CItem::Initialize(void)
{

}
int	 CItem::Progress(void)
{
	return 0;
}
void CItem::Render(HDC _hdc)
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
void CItem::Release(void)
{

}