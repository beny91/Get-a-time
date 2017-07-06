#include "StdAfx.h"
#include "Ui.h"

map<string, CBitBmp*>* CUi::m_mapBmp;

CUi::CUi(void)
{
}

CUi::CUi(string strName, float fx, float fy, float fcx, float fcy)
:m_tInfo(fx, fy, fcx, fcy)
,m_strName(strName)
{

}

CUi::~CUi(void)
{
}



void CUi::FrameMove(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime)
{
	if( m_dwFrameTime + _dwFrameDelayTime < GetTickCount() )
	{
		m_dwFrameTime = GetTickCount();

		++m_tFrame.m_iFrameStart;

		if(m_tFrame.m_iFrameStart > m_tFrame.m_iFrameEnd)
		{
			m_tFrame.m_iFrameStart = _iStart;

			if(m_dwState & STATE_ATTACK)
				m_dwState = STATE_STAND;
			if(m_dwState & STATE_NEUTRAL)
				m_dwState = STATE_STAND;
		}
	}

	if(m_dwState & _dwState)
	{
		if(m_tFrame.m_iImage != _iIamge)
		{
			m_tFrame.m_iFrameStart = _iStart;
		}

		m_tFrame.m_iFrameEnd = _iEnd;
		m_tFrame.m_iImage = _iIamge;
		m_tFrame.m_dwFrameTime = _dwFrameDelayTime;
	}
}
