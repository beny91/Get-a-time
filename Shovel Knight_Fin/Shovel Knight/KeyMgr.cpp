#include "StdAfx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = NULL;

CKeyMgr::CKeyMgr(void)
{
}

CKeyMgr::~CKeyMgr(void)
{
	Destroy();
}

void CKeyMgr::SetKeyState(void)
{
	m_dwKey = 0;
	
	if(GetAsyncKeyState(VK_RIGHT) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_RIGHT;
	}

	if(GetAsyncKeyState(VK_LEFT) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_LEFT;
	}

	if(GetAsyncKeyState(VK_UP) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_UP;
	}

	if(GetAsyncKeyState(VK_DOWN) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_DOWN;
	}

	if(GetAsyncKeyState(VK_SPACE) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_SPACE;
	}
	
	if(GetAsyncKeyState(VK_LBUTTON) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_LBUTTON;
	}

	if(GetAsyncKeyState(VK_CONTROL) )		//Ű�� ������ true��ȯ.
	{
		m_dwKey |= KEY_CRT;
	}

}

DWORD CKeyMgr::GetKeyState(void)
{
	return m_dwKey;
}
