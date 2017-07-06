#include "StdAfx.h"
#include "Obj.h"

map<string, CBitBmp*>* CObj::m_mapBmp;

POINT CObj::m_ptScroll;
POINT CObj::m_ptMapSize;

CObj::CObj(void)
{
}

CObj::CObj(string strName, float fx, float fy, float fcx, float fcy , int Hp , int Mp , int Att  )
:m_tInfo(fx, fy, fcx, fcy)
,m_strName(strName) , m_Hp(Hp), m_HpMax(Hp), m_Mp(Mp), m_MpMax(Mp), m_Att(Att)
{

}


CObj::~CObj(void)
{
}


int CObj::Progress(void)
{
	m_Rect.left		= long(m_tInfo.m_fX - m_tInfo.m_fCX / 2);
	m_Rect.top		= long(m_tInfo.m_fY - m_tInfo.m_fCY / 2);
	m_Rect.right	= long(m_tInfo.m_fX + m_tInfo.m_fCX / 2);
	m_Rect.bottom	= long(m_tInfo.m_fY + m_tInfo.m_fCY / 2);

	m_BodyRect.left		= long(m_tBodyBox.m_fX - m_tBodyBox.m_fCX / 2);
	m_BodyRect.top		= long(m_tBodyBox.m_fY - m_tBodyBox.m_fCY / 2);
	m_BodyRect.right	= long(m_tBodyBox.m_fX + m_tBodyBox.m_fCX / 2);
	m_BodyRect.bottom	= long(m_tBodyBox.m_fY + m_tBodyBox.m_fCY / 2);

	m_AttackRect.left	= long(m_tAttackBox.m_fX - m_tAttackBox.m_fCX / 2);
	m_AttackRect.top	= long(m_tAttackBox.m_fY - m_tAttackBox.m_fCY / 2);
	m_AttackRect.right	= long(m_tAttackBox.m_fX + m_tAttackBox.m_fCX / 2);
	m_AttackRect.bottom	= long(m_tAttackBox.m_fY + m_tAttackBox.m_fCY / 2);

	return 0;
}
void CObj::FrameMove(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime)
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
void CObj::FrameMoveReverse(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime)
{
	if( m_dwFrameTime + _dwFrameDelayTime < GetTickCount() )
	{
		m_dwFrameTime = GetTickCount();

		--m_tFrame.m_iFrameStart;

		if(m_tFrame.m_iFrameStart < m_tFrame.m_iFrameEnd)
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
void CObj::SetFrame(int _Start, int _End, int _iImage, DWORD _DealayTime)
{
	m_tFrame.m_iFrameStart = _Start;
	m_tFrame.m_iFrameEnd = _End;
	m_tFrame.m_iImage = _iImage;
	m_tFrame.m_dwFrameTime = _DealayTime;
}