#include "StdAfx.h"
#include "Background.h"
#include "OBJMGR.h"

CBackground::CBackground(void)
{
}

CBackground::~CBackground(void)
{
	Release();
}

CBackground::CBackground(string strName, float fx, float fy, float fcx, float fcy)
:CObj(strName, fx, fy, fcx, fcy)
{
	m_tFrame.m_iFrameStart=0;
	m_tFrame.m_iFrameEnd=0;
	m_tFrame.m_iImage=0;
}


void CBackground::Initialize(void)
{
	m_ScrollSpeed =7;
}

int CBackground::Progress(void)
{
	

	return 0;
}
void CBackground::Render(HDC _hdc)
{
	//BitBlt(_hdc, 
	//	static_cast<int>(m_tInfo.m_fX), static_cast<int>(m_tInfo.m_fY), 
	//	static_cast<int>(m_tInfo.m_fCX), static_cast<int>(m_tInfo.m_fCY),
	//	(*m_mapBmp)[m_strName.data()]->GetMemDC(),
	//	0,0,
	//	SRCCOPY);

	TransparentBlt(_hdc,
			static_cast<int>(m_tInfo.m_fX ),
			static_cast<int>(m_tInfo.m_fY),
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName.data()]->GetMemDC(),
	static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
		static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(0, 0, 0));		//빼고 싶은 색.s
}
void CBackground::Render2(HDC _hdc)
{
	//BitBlt(_hdc, 
	//	static_cast<int>(m_tInfo.m_fX), static_cast<int>(m_tInfo.m_fY), 
	//	static_cast<int>(m_tInfo.m_fCX), static_cast<int>(m_tInfo.m_fCY),
	//	(*m_mapBmp)[m_strName.data()]->GetMemDC(),
	//	0,0,
	//	SRCCOPY);

	TransparentBlt(_hdc,
			static_cast<int>(m_tInfo.m_fX )+ m_ptScroll.x/m_ScrollSpeed,
			static_cast<int>(m_tInfo.m_fY)+ m_ptScroll.y,
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName.data()]->GetMemDC(),
		0,			//출력되는 이미지의 시작 X값.
		0,
		static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
		static_cast<int>(m_tInfo.m_fCY),
		RGB(255, 255, 255));		//빼고 싶은 색.s
}

void CBackground::Release(void)
{
	
}


void CBackground::SetFrame(int _iFrameStart , int _iFrameEnd, int m_iImage, DWORD _dwFrameTime	)
{
	m_tFrame.m_iFrameStart = _iFrameStart;
	m_tFrame.m_iFrameEnd = _iFrameEnd;
	m_tFrame.m_iImage = m_iImage;
	m_tFrame.m_dwFrameTime = _dwFrameTime;
}