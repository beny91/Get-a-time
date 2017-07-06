#pragma once
#include "Define.h"

class CBitBmp;

class CUi
{
protected:
	string m_strName;

	INFO	m_tInfo;
	FRAME	m_tFrame;
	DWORD	m_dwFrameTime;
	DWORD	m_dwState;
public:
	static map<string, CBitBmp*>*		m_mapBmp;
	
	static void SetBitBmp(map<string, CBitBmp*>* mapBmp)
	{
		m_mapBmp = mapBmp;
	}
public:
	void FrameMove(DWORD _dwState, int _iStart, int _iEnd, int _iIamge, DWORD _dwFrameDelayTime);
public:
	virtual void Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	CUi(void);
	CUi(string strName, float fx, float fy, float fcx, float fcy);
	virtual ~CUi(void);
};
