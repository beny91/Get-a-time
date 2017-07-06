#include "StdAfx.h"
#include "BitBmp.h"

CBitBmp::CBitBmp(void)
{
}

CBitBmp::~CBitBmp(void)
{
	Release();
}

CBitBmp* CBitBmp::LoadBmp(PTCHAR pFileName)
{
	m_HDC = GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(m_HDC);	//또 다른 DC를 만들어서 실제 이미지를 그린다.

	m_Bitmap = (HBITMAP)LoadImage(NULL, pFileName
		, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(!m_Bitmap)		//이미지 로드 실패시 NULL반환.
		MessageBox(g_hWnd, pFileName, L"이미지 로드 실패!", NULL);


	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	ReleaseDC(g_hWnd, m_HDC);

	return this;
}

void CBitBmp::Release(void)
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);

	DeleteDC(m_MemDC);
}
