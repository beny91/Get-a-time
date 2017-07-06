#include "StdAfx.h"
#include "MyFont.h"


CMyFont::CMyFont(void)
{
}
CMyFont::CMyFont(string strName, float fx, float fy, float fcx, float fcy)
:CUi(strName, fx, fy, fcx, fcy)
{

}

CMyFont::~CMyFont(void)
{
}

void CMyFont::Initialize(void)
{
	m_iStart = 0;
	m_iEnd=9;
	m_iPosition=0;
	m_tFrame = FRAME(0,8,0,100);
	m_dwFrameTime=GetTickCount();
	
}
int CMyFont::Progress(void)
{	
	CheckNumber();
	FrameMove(STATE_STAND, m_iStart, m_iEnd, 0, 80);
	return 0;
}
void CMyFont::Render(HDC _hdc)
{
	//TransparentBlt(_hdc,
	//	static_cast<int>(m_tInfo.m_fX  ),
	//	static_cast<int>(m_tInfo.m_fY ),
	//	static_cast<int>(m_tInfo.m_fCX ),
	//	static_cast<int>(m_tInfo.m_fCY ),
	//	(*m_mapBmp)[m_strName]->GetMemDC(),
	//	static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX),			//출력되는 이미지의 시작 X값.
	//	static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY),
	//	static_cast<int>(m_tInfo.m_fCX),		//이미지 출력 범위 지정.
	//	static_cast<int>(m_tInfo.m_fCY),
	//	RGB(0, 255, 255));		//빼고 싶은 색.s

		BitBlt(_hdc, 
		static_cast<int>(m_tInfo.m_fX),
		static_cast<int>(m_tInfo.m_fY),
		static_cast<int>(m_tInfo.m_fCX),
		static_cast<int>(m_tInfo.m_fCY),
		(*m_mapBmp)[m_strName]->GetMemDC(),
		static_cast<int>(m_tFrame.m_iFrameStart * m_tInfo.m_fCX), // 이미지의 x
		static_cast<int>(m_tFrame.m_iImage * m_tInfo.m_fCY), // 이미지의 y
		SRCCOPY);	

}

void CMyFont::Release()
{

}

void CMyFont::SetFrame(int _iStart , int _iEnd, int _iImage , int _iFrameTime)
{
	m_tFrame.m_iFrameStart = _iStart;
	m_tFrame.m_iFrameEnd = _iEnd ;
	m_tFrame.m_iImage = _iImage;
	m_tFrame.m_dwFrameTime = _iFrameTime;
}
void CMyFont::CheckNumber(void)
{
	// 자리마다 받아온 값을 계산해서 스프라이트를 띄어준다.
	switch(m_iPosition)
	{ 
	case 1:
		m_tFrame.m_iFrameStart = m_iNum % 10;
		m_tFrame.m_iFrameEnd = m_iNum % 10;
		m_iStart=m_iNum % 10;
		break;
	case 2:
		m_tFrame.m_iFrameStart = (m_iNum % 100)/10;
		m_tFrame.m_iFrameEnd = (m_iNum % 100)/10;
		m_iStart=(m_iNum % 100)/10;
		break;
	case 3:
		m_tFrame.m_iFrameStart = (m_iNum % 1000)/100;
		m_tFrame.m_iFrameEnd = (m_iNum % 1000)/100;
		m_iStart=(m_iNum % 1000)/100;
		break;
	case 4:
		m_tFrame.m_iFrameStart = m_iNum /1000;
		m_tFrame.m_iFrameEnd = m_iNum /1000;
		m_iStart= m_iNum /1000;
		break;
	}

	switch(m_iLifePos)
	{
		case 1:
			if( m_iNum >= 20 )
			{
				m_tFrame.m_iFrameStart = 0;
				m_tFrame.m_iFrameEnd = 0;
				m_iStart= 0;
				m_iEnd = 0;
			}
			else if(  m_iNum  <= 20 && m_iNum  >= 10 )
			{
				m_tFrame.m_iFrameStart = 1;
				m_tFrame.m_iFrameEnd = 1;
				m_iStart= 1;
				m_iEnd = 1;
			}
			else if( m_iNum  <= 10)
			{
				m_tFrame.m_iFrameStart = 2;
				m_tFrame.m_iFrameEnd = 2;
				m_iStart= 2;
				m_iEnd = 2;
			}
			
			
		break;
		case 2:
			if( m_iNum >= 40 )
			{
				m_tFrame.m_iFrameStart = 0;
				m_tFrame.m_iFrameEnd = 0;
				m_iStart= 0;
				m_iEnd = 0;
			}
			else if(  m_iNum  <= 40 && m_iNum  >= 30 )
			{
				m_tFrame.m_iFrameStart = 1;
				m_tFrame.m_iFrameEnd = 1;
				m_iStart= 1;
				m_iEnd = 1;
			}
			else if( m_iNum  <= 30)
			{
				m_tFrame.m_iFrameStart = 2;
				m_tFrame.m_iFrameEnd = 2;
				m_iStart= 2;
				m_iEnd = 2;
			}
		break;
		case 3:
			if( m_iNum >= 60 )
			{
				m_tFrame.m_iFrameStart = 0;
				m_tFrame.m_iFrameEnd = 0;
				m_iStart= 0;
				m_iEnd = 0;
			}
			else if(  m_iNum  <= 60 && m_iNum  >= 50 )
			{
				m_tFrame.m_iFrameStart = 1;
				m_tFrame.m_iFrameEnd = 1;
				m_iStart= 1;
				m_iEnd = 1;
			}
			else if( m_iNum  <= 50)
			{
				m_tFrame.m_iFrameStart = 2;
				m_tFrame.m_iFrameEnd = 2;
				m_iStart= 2;
				m_iEnd = 2;
			}
		break;
		case 4:
			if( m_iNum >= 80 )
			{
				m_tFrame.m_iFrameStart = 0;
				m_tFrame.m_iFrameEnd = 0;
				m_iStart= 0;
				m_iEnd = 0;
			}
			else if(  m_iNum  <= 80 && m_iNum  >= 70 )
			{
				m_tFrame.m_iFrameStart = 1;
				m_tFrame.m_iFrameEnd = 1;
				m_iStart= 1;
				m_iEnd = 1;
			}
			else if( m_iNum  <= 70)
			{
				m_tFrame.m_iFrameStart = 2;
				m_tFrame.m_iFrameEnd = 2;
				m_iStart= 2;
				m_iEnd = 2;
			}

		break;
	}
}
