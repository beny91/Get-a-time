#pragma once

#include "Define.h"

class CBitBmp
{
private:
	HDC			m_HDC, m_MemDC;		//m_MemDC���� �׸��� ����Ǵ� DC
	HBITMAP		m_Bitmap, m_OldBitmap;

public:
	HDC	GetMemDC(void){	return m_MemDC;	}

public:
	CBitBmp*	LoadBmp(PTCHAR pFileName);
	void		Release(void);

public:
	CBitBmp(void);
	~CBitBmp(void);
};
