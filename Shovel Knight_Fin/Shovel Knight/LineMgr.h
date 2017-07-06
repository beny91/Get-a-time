#pragma once

#include "define.h"

class CLineMgr
{
private:
	static CLineMgr* m_pInstance;

	LINE m_Line;

public:
	list<LINE*> m_Linelist;

public:
	static CLineMgr* GetInstance(void)
	{
		if( m_pInstance == NULL)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}

	void Destroy (void)
	{
		SAFE_DELETE(m_pInstance);
		m_pInstance=NULL;
	}
public:
	void DrawLine(void);

	void SaveLine(void);
	void LoadLine(void);

public:

	list<LINE*>* GetLineList(void);

private:
	CLineMgr(void);
public:
	~CLineMgr(void);
};
