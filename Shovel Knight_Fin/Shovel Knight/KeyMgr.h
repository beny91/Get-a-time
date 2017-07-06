#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	static CKeyMgr* m_pInstance;

public:
	static CKeyMgr* GetInstance(void)
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CKeyMgr;
		}
		return m_pInstance;
	}

	void Destroy(void)
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	DWORD		m_dwKey;

public:
	void SetKeyState(void);
	DWORD GetKeyState(void);

private:
	CKeyMgr(void);
public:
	~CKeyMgr(void);
};
